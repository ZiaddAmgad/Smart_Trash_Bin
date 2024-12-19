#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Common settings used in most of the pico_w examples
// (see https://www.nongnu.org/lwip/2_1_x/group__lwip__opts.html for details)

// Allow DHCP to be enabled
#define LWIP_DHCP                  1

// Predefine platform endianness (this is needed on arm32 anyway)
#define BYTE_ORDER LITTLE_ENDIAN

// Enable UDP
#define LWIP_UDP                   1

// Enable TCP
#define LWIP_TCP                   1

// Enable DNS (needed for HTTP)
#define LWIP_DNS                   1

// Specify NO_SYS because we are running without an RTOS
#define NO_SYS                     1
#define LWIP_CALLBACK_API         1

// Allow socket/netconn usage rather than pure raw API
#define LWIP_NETCONN              0
#define LWIP_SOCKET               0

// Optional: Disable sanity checks (use with caution)
#define LWIP_DISABLE_TCP_SANITY_CHECKS 1
// Memory settings
#define MEM_ALIGNMENT             4
#define MEM_SIZE                  4000
#define MEMP_NUM_TCP_PCB         5
#define MEMP_NUM_ARP_QUEUE       10
#define MEMP_NUM_TCP_SEG         16
#define PBUF_POOL_SIZE           24
#define LWIP_ARP                 1
#define LWIP_ETHERNET            1
#define LWIP_ICMP               1
#define LWIP_RAW                1
#define TCP_WND                 (8 * TCP_MSS)
#define TCP_MSS                 1460
#define TCP_SND_BUF            (8 * TCP_MSS)
#define TCP_SND_QUEUELEN       16
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK   1
#define LWIP_NETIF_HOSTNAME        1
#define LWIP_NETCONN_SEM_PER_THREAD 0

#define ETHARP_DEBUG                LWIP_DBG_OFF
#define NETIF_DEBUG                 LWIP_DBG_OFF
#define PBUF_DEBUG                  LWIP_DBG_OFF
#define API_LIB_DEBUG              LWIP_DBG_OFF
#define API_MSG_DEBUG              LWIP_DBG_OFF
#define SOCKETS_DEBUG              LWIP_DBG_OFF
#define ICMP_DEBUG                 LWIP_DBG_OFF
#define INET_DEBUG                 LWIP_DBG_OFF
#define IP_DEBUG                   LWIP_DBG_OFF
#define IP_REASS_DEBUG            LWIP_DBG_OFF
#define RAW_DEBUG                 LWIP_DBG_OFF
#define MEM_DEBUG                 LWIP_DBG_OFF
#define MEMP_DEBUG                LWIP_DBG_OFF
#define SYS_DEBUG                 LWIP_DBG_OFF
#define TCP_DEBUG                 LWIP_DBG_OFF
#define TCP_INPUT_DEBUG           LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG          LWIP_DBG_OFF
#define TCP_RTO_DEBUG             LWIP_DBG_OFF
#define TCP_CWND_DEBUG            LWIP_DBG_OFF
#define TCP_WND_DEBUG             LWIP_DBG_OFF
#define TCP_FR_DEBUG              LWIP_DBG_OFF
#define TCP_QLEN_DEBUG            LWIP_DBG_OFF
#define TCP_RST_DEBUG             LWIP_DBG_OFF
#define UDP_DEBUG                 LWIP_DBG_OFF

#endif /* __LWIPOPTS_H__ */