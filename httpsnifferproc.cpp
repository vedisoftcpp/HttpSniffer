#include "httpsnifferproc.h"
#include "httpstatistics.h"
#include "HttpStataEntry.h"

namespace HttpSniffer
{

HttpSnifferProc::HttpSnifferProc(void* data) :
    _http_statistics((HttpStatistics*)data)
{
}

/* 4 bytes IP address */
typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

/* IPv4 header */
typedef struct ip_header{
    u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    u_char  tos;            // Type of service
    u_short tlen;           // Total length
    u_short identification; // Identification
    u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;            // Time to live
    u_char  proto;          // Protocol
    u_short crc;            // Header checksum
    ip_address  saddr;      // Source address
    ip_address  daddr;      // Destination address
    u_int   op_pad;         // Option + Padding
}ip_header;

/* prototype of the packet handler */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

using std::vector;

typedef vector<u_char> ip_packet_t;

using std::map;
map<u_short, vector<ip_packet_t> > ip_packets_buffer;

struct fragmented_ordering
{
    bool operator() (const ip_packet_t& p1, const ip_packet_t& p2) const
    {
        // ip headers
        ip_header* h1 = (ip_header*)&p1[0];
        ip_header* h2 = (ip_header*)&p2[0];

        // fragment offsets
        u_short fo1 = h1->flags_fo >> 3;
        u_short fo2 = h2->flags_fo >> 3;

        return fo1 < fo2;
    }
};

typedef vector<u_char> tcp_packet_t;
map<u_int, vector<u_char> > tcp_data_buffer;

struct tcp_header
{
    u_short src_port;
    u_short dst_port;
    u_int seq_number;
    u_int ask_number;
    u_char stuff;
    u_char flags;
    u_short window;
    u_short checksum;
    u_short urg_ptr;
};

vector<u_char> get_tcp_data_from_tcp_packet(tcp_header* th, u_int size)
{
    vector<u_char> data;
    u_int data_offset = (th->stuff >> 4) * 4;
    for (u_int i=data_offset; i<size; i++)
        data.push_back(*((u_char*)th+i));
    return data;
}

vector<u_char> get_tcp_data_from_ip_packet(ip_header* ih)
{
    u_short data_offset = (ih->ver_ihl & 0x0f)*4;
    tcp_header* th = (tcp_header*)((u_char*)ih + data_offset);
    return get_tcp_data_from_tcp_packet(th, ntohs(ih->tlen) - data_offset);
}

void HttpSnifferProc::operator()()
{
//    int i = 0;
//    while (true)
//    {
//        ::Sleep(1000);
//        i++;

//        //std::cout << "\nSNIFFER PROC:" << i << "\n";

//        (*_http_statistics) << i;

//        //std::cout << "\nSNIFFER PROC2:" << i << "\n";
//    }

    pcap_if_t *alldevs;
    pcap_if_t *d;
    int inum;
    int i=0;
    pcap_t *adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_int netmask;
    char packet_filter[] = "ip";
    struct bpf_program fcode;

    /* Retrieve the device list */
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }

    /* Print the list */
    for(d=alldevs; d; d=d->next)
    {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
    }

    if(i==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return;
    }

    printf("Enter the interface number (1-%d):",i);
    scanf_s("%d", &inum);

    if(inum < 1 || inum > i)
    {
        printf("\nInterface number out of range.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return;
    }

    /* Jump to the selected adapter */
    for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

    /* Open the adapter */
    if ( (adhandle= pcap_open(d->name,  // name of the device
                              65536,     // portion of the packet to capture.
                              // 65536 grants that the whole packet will be captured on all the MACs.
                              PCAP_OPENFLAG_PROMISCUOUS,         // promiscuous mode
                              1000,      // read timeout
                              NULL,      // remote authentication
                              errbuf     // error buffer
                              ) ) == NULL)
    {
        fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return;
    }

    /* Check the link layer. We support only Ethernet for simplicity. */
    if(pcap_datalink(adhandle) != DLT_EN10MB)
    {
        fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return;
    }

    if(d->addresses != NULL)
        /* Retrieve the mask of the first address of the interface */
        netmask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        /* If the interface is without addresses we suppose to be in a C class network */
        netmask=0xffffff;


    //compile the filter
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
    {
        fprintf(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return;
    }

    //set the filter
    if (pcap_setfilter(adhandle, &fcode)<0)
    {
        fprintf(stderr,"\nError setting the filter.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return;
    }

    printf("\nlistening on %s...\n", d->description);

    /* At this point, we don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);

    /* start the capture */
    pcap_loop(adhandle, 0, packet_handler, NULL);
}

void HttpSnifferProc::eject_url(const std::vector<u_char>& data)
{
    std::string _data(data.begin(), data.end());
//    std::cout << "*****************" << "\n";
//    std::cout << _data << "\n";

    std::cout << "*****************" << "\n";
    std::cout << "*****************" << "\n";
    std::cout << "*****************" << "\n";

    for (size_t pos = _data.find("Host: ");
         pos != std::string::npos;
         pos = _data.find("Host: ", pos+6))
    {
        size_t eol = _data.find("\r\n", pos);
        if (eol == std::string::npos)
            return;
        std::string url(_data.begin()+pos+6, _data.begin()+eol);
        std::cout << url << "\n";
    }

    std::cout << "*****************" << "\n";
    std::cout << _data << "\n";

    std::cout << "*****************" << "\n";
    std::cout << "*****************" << "\n";
    std::cout << "*****************" << "\n\n\n";

    HttpStataEntry entry;
    (*_http_statistics) << entry;
}

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    ip_header *ih;
    ih = (ip_header *) (pkt_data + 14);

    // check for TCP
    if (ih->proto != 0x06)
        return;

    //vector<u_char> ip_packet(ntohs(ih->tlen));
    vector<u_char> ip_packet;
    for (int i = 0; i < ntohs(ih->tlen); ++i)
        ip_packet.push_back( *((u_char*)ih+i) );

    // checking for fragmentation
    u_short DF_flag = (ntohs(ih->flags_fo) >> 13) & 0x02;
    u_short MF_flag = (ntohs(ih->flags_fo) >> 13) & 0x04;

    if (!DF_flag)
    {
        u_short fo = ntohs(ih->flags_fo) & 0x1fff;
        if (!MF_flag && !fo)
            goto TCP_PACKET_PROCESSING;

        // have all ip-packets was recived
        map<u_short, vector<ip_packet_t> >::iterator it = ip_packets_buffer.find(ntohs(ih->identification));
        if (it == ip_packets_buffer.end())
        {
            // there aren't ip-packet with same id in buffer
            vector<ip_packet_t> fragmented_packets;
            fragmented_packets.push_back(ip_packet);
            ip_packets_buffer[ntohs(ih->identification)] = fragmented_packets;
            return;
        }
        else
        {
            // there are ip-packet with same id in buffer

            // fragmented packets (fpackets)
            vector<ip_packet_t>& fpackets = ip_packets_buffer[ntohs(ih->identification)];

            fpackets.push_back(ip_packet);
            std::sort(fpackets.begin(), fpackets.end(), fragmented_ordering());

            // try to merge
            ip_header *first_packet_header = (ip_header*)&(fpackets[0][0]);

            // fragment offset
            u_short firt_packet_fo = ntohs(first_packet_header->flags_fo) & 0x1fff;
            if (firt_packet_fo != 0)
            {
                // there isn't first packet
                return;
            }

            u_char MF_flag = 0x04;
            u_short first_packet_data_len = ntohs(first_packet_header->tlen) -
                                            (first_packet_header->ver_ihl & 0x0f)*4;
            u_short data_len = first_packet_data_len;
            vector<ip_packet_t>::iterator it;
            for (it = fpackets.begin()+1; it != fpackets.end(); ++it)
            {
                ip_header *packet_header = (ip_header*)&((*it)[0]);
                u_short fo = ntohs(packet_header->flags_fo) & 0X1fff;

                if (fo != data_len/8)
                {
                    // not all packets was recived
                    return;
                }

                data_len += ntohs(packet_header->tlen) -
                            (packet_header->ver_ihl & 0x0f)*4;
                MF_flag *= (ntohs(packet_header->flags_fo) >> 13) & 0x04;
            }
            if (MF_flag != 0)
            {
                // there isn't last packet
                return;
            }

            // now we can merge fragmented packets

            // first packet header length + common data length
            first_packet_header->tlen = htons((first_packet_header->ver_ihl & 0x0f)*4 + data_len);

            // data without first packet data
            //vector<u_char> data_add(data_len - first_packet_data_len);
            vector<u_char> data_add;
            for (it = fpackets.begin()+1; it != fpackets.end(); ++it)
            {
                ip_header* packet_header = (ip_header*)&((*it)[0]);
                u_short offset = (packet_header->ver_ihl & 0x0f)*4;
                for (u_short i = offset; i < ntohs(packet_header->tlen); ++i)
                    data_add.push_back( *((u_char*)packet_header+i) );
            }

            // merge first packet data and rest data
            ip_packet_t merged_packet = fpackets[0];
            merged_packet.insert(merged_packet.end(), data_add.begin(), data_add.end());
            ip_packet = merged_packet;

            ip_packets_buffer.erase(ntohs(ih->identification));
            goto TCP_PACKET_PROCESSING;
        }
    }

TCP_PACKET_PROCESSING:

    ih = (ip_header *) &ip_packet[0];
    u_short data_offset = (ih->ver_ihl & 0x0f)*4;
    tcp_header* th = (tcp_header*)((u_char*)ih + data_offset);

    if ( ntohs(th->dst_port) == 80 )
    {
        // packet from localhost

        std::cout << "\npacket from localhost\n\n" << std::endl;

        u_int tcp_id = *((u_int*)&(ih->daddr));

        // FIN
        if (th->flags & 0x01)
        {
            //std::cout << "FIN 1\n";
            eject_url(tcp_data_buffer[tcp_id]);
            tcp_data_buffer.erase(tcp_id);
            return;
        }

        // SYN
        if (th->flags & 0x02)
        {
            map<u_int, vector<u_char> >::iterator it = tcp_data_buffer.find(tcp_id);
            if (it != tcp_data_buffer.end())
            {
                eject_url(tcp_data_buffer[tcp_id]);
            }
            tcp_data_buffer[tcp_id] = get_tcp_data_from_ip_packet(ih);
            return;
        }

        vector<u_char> data = get_tcp_data_from_ip_packet(ih);
        vector<u_char>& data_buffer = tcp_data_buffer[tcp_id];
        data_buffer.insert(data_buffer.end(), data.begin(), data.end());
    }
    else if ( ntohs(th->src_port) == 80 )
    {
        // packet to localhost

        u_int tcp_id = *((u_int*)&(ih->saddr));

        // FIN
        if (th->flags & 0x01)
        {
            //std::cout << "FIN 2\n";
            eject_url(tcp_data_buffer[tcp_id]);
            tcp_data_buffer.erase(tcp_id);
            return;
        }
    }

}

}
