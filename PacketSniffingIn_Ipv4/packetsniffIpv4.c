/*-----------------------------------------------------------------------------------------------
HyunJun Kwon
권현준
------------------------------------------------------------------------------------------------*/
// Header files inclusion
#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

// Define constants
#define SNAP_LEN 1518 // Default snap length
#define SIZE_ETHERNET 14 // Size of ethernet headers
#define ETHER_ADDR_LEN	6 // Length of ethernet address


/*struct tm * time_info;
time_t nowtime;
char timeString[9];
nowtime = header->ts.tv_sec;
time_info = localtime(&nowtime);
strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);*/
// Define struct

struct sniff_ethernet // Ethernet header
{
	u_char ether_dhost[ETHER_ADDR_LEN]; // Destination host address
	u_char ether_shost[ETHER_ADDR_LEN]; // Source host address
	u_short ether_type; // Types: IP||ARP||RARP||etc
};
struct sniff_ip // IP header
{
	u_char  ip_vhl;  // version << 4 | header length >> 2
	u_char  ip_tos;  // type of service
	u_short ip_len;  // total length
	u_short ip_id;  // identification
	u_short ip_off;  // fragment offset field
	#define IP_RF 0x8000  // reserved fragment flag
	#define IP_DF 0x4000  // dont fragment flag
	#define IP_MF 0x2000  // more fragments flag
	#define IP_OFFMASK 0x1fff  // mask for fragmenting bits
	u_char  ip_ttl;  // time to live
	u_char  ip_p;  // protocol
	u_short ip_sum;  // checksum
	struct  in_addr ip_src,ip_dst; // source and dest address
};
#define IP_HL(ip) (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip) (((ip)->ip_vhl) >> 4)
typedef u_int tcp_seq;
struct sniff_tcp // TCP Header
{
	u_short th_sport;  // source port
	u_short th_dport;  // destination port
	tcp_seq th_seq;    // sequence number
	tcp_seq th_ack;   // acknowledgement number
	u_char  th_offx2; // data offset, rsvd
	#define TH_OFF(th) (((th)->th_offx2 & 0xf0) >> 4)
	u_char  th_flags;
	#define TH_FIN  0x01
	#define TH_SYN  0x02
	#define TH_RST  0x04
	#define TH_PUSH 0x08
	#define TH_ACK  0x10
	#define TH_URG  0x20
	#define TH_ECE  0x40
	#define TH_CWR  0x80
	#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	u_short th_win; // window
	u_short th_sum; // checksum
	u_short th_urp; // urgent pointer
};
/*typedef struct pcaprec_hdr_s
{
	guint32 ts_sec;
	guint32 ts_usec;
	guint32 incl_len;
	guint32 orig_len;
};*/
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
void print_payload(const u_char *payload, int len);
void print_hex_ascii_line(const u_char *payload, int len, int offset);
// Function definition
void print_hex_ascii_line(const u_char *payload, int len, int offset)
{
	// Local variables declare
	int i;
	int gap;
	const u_char *ch;

	// Statements
	// offset
	printf("%05d   ", offset);

	// hex
	ch = payload;
	for(i = 0; i < len; i++)
	{
		printf("%02x ", *ch);
		ch++;
		// print extra space after 8th byte for visual aid
		if (i == 7)
			printf(" ");
	}
	// print space to handle line less than 8 bytes
	if (len < 8)
		printf(" ");

	// fill hex gap with spaces if not full line
	if (len < 16)
	{
		gap = 16 - len;
		for (i = 0; i < gap; i++)
		{
			printf("   ");
		}
	}
	printf("   ");

	// ascii (if printable)
	ch = payload;
	for(i = 0; i < len; i++)
	{
		if (isprint(*ch))
			printf("%c", *ch);
		else
			printf(".");
		ch++;
	}
	printf("\n");
	return;
}
void print_payload(const u_char * payload, int len)
{
	// Local variables declrea
	int len_rem = len;
	int line_width = 16; // number of bytes per line
	int line_len;
	int offset = 0;
	const u_char *ch = payload;

	// Statements
	if (len <= 0)
		return;
	if (len <= line_width) // data fits on one line
	{
		print_hex_ascii_line(ch, len, offset);
		return;
	}
	for ( ;; ) // data spans multiple lines
	{
		line_len = line_width % len_rem;
		print_hex_ascii_line(ch, line_len, offset);
		len_rem = len_rem - line_len;
		ch = ch + line_len;
		offset = offset + line_width;
		if (len_rem <= line_width)
		{
			print_hex_ascii_line(ch, len_rem, offset);
			break;
		}
	}
	return;
}
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	// Localvariables declare
	static int count = 1;  // packet counter
	const struct sniff_ethernet *ethernet; // The ethernet header [1]
	const struct sniff_ip *ip; // The IP header
	const struct sniff_tcp *tcp; // The TCP header
	const struct pcaprec_hdr_s *ti;
	const char *payload; // Packet payload
	int size_ip;
	int size_tcp;
	int size_payload;

	struct tm * time_info;
	time_t nowtime;
	char timeString[9];
	nowtime = header->ts.tv_sec;
	time_info = localtime(&nowtime);
	strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
	// Statements
	printf("Arrival Time: %s.%06d\n", timeString, header->ts.tv_usec);
	printf("\nPacket number %d:\n", count);
	count++;

	ethernet = (struct sniff_ethernet*)(packet); // define ethernet header
	printf("From (Mac): %02x:%02x:%02x:%02x:%02x:%02x\n",
		 (unsigned)ethernet->ether_dhost[0],
		 (unsigned)ethernet->ether_dhost[1],
		 (unsigned)ethernet->ether_dhost[2],
		 (unsigned)ethernet->ether_dhost[3],
		 (unsigned)ethernet->ether_dhost[4],
		 (unsigned)ethernet->ether_dhost[5]);
	printf("To (Mac): %02x:%02x:%02x:%02x:%02x:%02x\n",
		 (unsigned)ethernet->ether_shost[0],
		 (unsigned)ethernet->ether_shost[1],
		 (unsigned)ethernet->ether_shost[2],
		 (unsigned)ethernet->ether_shost[3],
		 (unsigned)ethernet->ether_shost[4],
		 (unsigned)ethernet->ether_shost[5]);
	// define/compute ip header offset
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20)
	{
		printf("Invalid IP header length: %u bytes\n", size_ip);
		return;
	}
	printf("From: %s\n", inet_ntoa(ip->ip_src));
	printf("To: %s\n", inet_ntoa(ip->ip_dst));
	// determine protocol
	switch(ip->ip_p)
	{
		case IPPROTO_TCP:
			printf("Protocol: TCP\n");
			break;
		case IPPROTO_UDP:
			printf("Protocol: UDP\n");
			return;
		case IPPROTO_ICMP:
			printf("Protocol: ICMP\n");
			return;
		case IPPROTO_IP:
			printf("Protocol: IP\n");
			return;
		default:
			printf("Protocol: unknown\n");
			return;
	}
	printf("Id(Hex): %#0x\n", ntohs(ip->ip_id));
	printf("IP_OFF(Hex): %x\n", ntohs(ip->ip_off));
	printf("Id(Dec): %d\n", (unsigned)ntohs(ip->ip_id));
	switch(IP_DF)
	{
	case 0x8000:
	{
		printf("Flags: RF\n");
		break;
	}
	case 0x4000:
	{
		printf("Flags: DF\n");
		break;
	}
	case 0x2000:
	{
		printf("Flags: MF\n");
		break;
	}
	case 0x1fff:
	{
		printf("Flags: OFFMASK\n");
		break;
	}
	}
	printf("Captured len: %d\n", header->caplen);
	printf("Actual len: %d\n", header->len);
	printf("IP header len: %d\n", size_ip);
	// define/compute tcp header offset
	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp) * 4;
	if (size_tcp < 20)
	{
		printf("Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}
	printf("Src port: %d\n", ntohs(tcp->th_sport));
	printf("Dst port: %d\n", ntohs(tcp->th_dport));

	// define/compute tcp payload (segment) offset
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
	// compute tcp payload (segment) size
	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

	if (size_payload > 0)
	{
		printf("Payload (%d bytes):\n", size_payload);
		print_payload(payload, size_payload);
	}
	return;
}
int main(int argc, char **argv)
{
	// Local variables declare
	char *dev = NULL;	// capture device name
	char errbuf[PCAP_ERRBUF_SIZE]; // error buffer
	pcap_t *handle; // packet capture handle
	char filter_exp[] = "tcp||udp||icmp";	// filter expression
	struct bpf_program fp;	// compiled filter program (expression)
	bpf_u_int32 mask;	// subnet mask
	bpf_u_int32 net; // ip
	int num_packets = 500; // number of packets to capture

	// Statements
	if (argc == 2) //check for capture device name on command-line
	{
		dev = argv[1];
	}
	else if (argc > 2)
	{
		fprintf(stderr, "error: unrecognized command-line options\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		// find a capture device if not specified on command-line
		dev = pcap_lookupdev(errbuf);
		if (dev == NULL)
		{
			fprintf(stderr, "Couldn't find default interface: %s\n", errbuf);
			exit(EXIT_FAILURE);
		}
	}
	// get network number and mask associated with capture device
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		fprintf(stderr, "Couldn't get netmask for interface %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}
	// print capture info
	printf("Interface: %s\n", dev);
	printf("Number of packets: %d\n", num_packets);
	printf("Filter expression: %s\n", filter_exp);
	// open capture device
	handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);
	if (handle == NULL)
	{
		fprintf(stderr, "Couldn't open interface %s: %s\n", dev, errbuf);
		exit(EXIT_FAILURE);
	}
	if (pcap_datalink(handle) != DLT_EN10MB)
	{
		fprintf(stderr, "%s is not an Ethernet\n", dev);
		exit(EXIT_FAILURE);
	}
	// compile the filter expression
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
	{
		fprintf(stderr, "Couldn't parse filter %s: %s\n",
		    filter_exp, pcap_geterr(handle));
		exit(EXIT_FAILURE);
	}
	// apply the compiled filter
	if (pcap_setfilter(handle, &fp) == -1)
	{
		fprintf(stderr, "Couldn't install filter %s: %s\n",
		    filter_exp, pcap_geterr(handle));
		exit(EXIT_FAILURE);
	}
	pcap_loop(handle, num_packets, got_packet, NULL);
	pcap_freecode(&fp);
	pcap_close(handle);
	printf("\nDONE!\n");

	return 0;
}
