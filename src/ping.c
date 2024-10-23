#include "lwip/icmp.h"
#include "lwip/inet_chksum.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/timeouts.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/sockets.h"
#include "lwip/err.h"
#include <stdio.h>

#define PING_ID 0xAFAF
#define PING_DATA_SIZE 32

static u16_t ping_seq_num;

struct icmp_echo_hdr *ping_create_echo_req(u16_t len) {
    struct pbuf *p = pbuf_alloc(PBUF_IP, len, PBUF_RAM);
    if (!p) return NULL;

    struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)p->payload;
    iecho->id = PING_ID;
    iecho->seqno = lwip_htons(++ping_seq_num);
    iecho->type = ICMP_ECHO;
    iecho->code = 0;
    iecho->chksum = 0;

    memset((u8_t *)iecho + sizeof(struct icmp_echo_hdr), 0, len - sizeof(struct icmp_echo_hdr));
    iecho->chksum = inet_chksum(iecho, len);

    return iecho;
}

void ping_send(const ip_addr_t *addr) {
    struct pbuf *p = pbuf_alloc(PBUF_IP, sizeof(struct icmp_echo_hdr) + PING_DATA_SIZE, PBUF_RAM);
    if (!p) return;

    struct icmp_echo_hdr *iecho = ping_create_echo_req(sizeof(struct icmp_echo_hdr) + PING_DATA_SIZE);

    ip_addr_t dest;
    ip_addr_copy(dest, *addr);

    if (iecho != NULL) {
        printf("Pinging %s with ICMP...\n", ipaddr_ntoa(&dest));
        if (ip_output(p, NULL, addr, 1, 0, IP_PROTO_ICMP) != ERR_OK) {
            printf("Ping failed!\n");
        }
    }

    pbuf_free(p);
}
