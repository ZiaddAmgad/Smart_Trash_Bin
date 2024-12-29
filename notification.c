#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Pico SDK includes
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include "pico/rand.h"

// LWIP includes
#include "lwip/opt.h"
#include "lwip/ip_addr.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"
#include "lwip/sockets.h"

// pico-http-client include
#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/certs.h" // For certificate verification (if needed)
#include "mbedtls/x509.h"
#include "mbedtls/platform.h"
#include "mbedtls/ssl.h"

// Replace these with your actual values


// Buffer for the HTTP request
static char http_request[512];
static struct tcp_pcb *tcp_pcb;
static bool wifi_connected = false;

const char IFTTT_HOST[] = "maker.ifttt.com"; // IFTTT Webhooks API Host
const char IFTTT_PATH[] = "/trigger/..."; // Make an Applet of a webhook and your desired notification and use the Applet's API key provided upon creation   
const int IFTTT_PORT = 80;
// Callback for TCP connection
// Callback for TCP connection
// Callback for TCP connection
static err_t tcp_connected(void *arg, struct tcp_pcb *tpcb, err_t err) {
    if (err == ERR_OK) {
        printf("Successfully connected to IFTTT server.\n");
        printf("Sending HTTP request...\n");

        // JSON payload or data to send
        const char *json_payload = "{\"value1\":\"🗑️ Alert: Trash bin is full! Time to take out the trash.\"}";

        // Construct the HTTP POST request to trigger IFTTT Webhook
        snprintf(http_request, sizeof(http_request),
                 "POST %s HTTP/1.1\r\n"
                 "Host: %s\r\n"
                 "Content-Type: application/json\r\n"
                 "Content-Length: %zu\r\n"
                 "Connection: close\r\n"
                 "\r\n"
                 "%s",
                 IFTTT_PATH,
                 IFTTT_HOST,
                 strlen(json_payload),
                 json_payload);

        printf("Constructed HTTP Request:\n%s\n", http_request);

        // Send the request to IFTTT
        err_t write_err = tcp_write(tpcb, http_request, strlen(http_request), TCP_WRITE_FLAG_COPY);
        if (write_err == ERR_OK) {
            tcp_output(tpcb);
        } else {
            printf("Failed to send HTTP request: %d\n", write_err);
        }
    } else {
        printf("Failed to connect to server: %d\n", err);
    }
    return ERR_OK;
}



// Update hostname and port for Zapier Webhook


// TCP receive callback
static err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (p == NULL) {
        // Connection closed by remote host
        printf("Connection closed by server.\n");
        tcp_close(tpcb);
        return ERR_OK;
    }

    // Print the response from the server
    printf("Received response from Pushbullet:\n%.*s\n", p->len, (char *)p->payload);

    // Free the buffer
    pbuf_free(p);
    return ERR_OK;
}

// TCP error callback
static void tcp_error_callback(void *arg, err_t err) {
    printf("TCP error: %d\n", err);
    if (tcp_pcb != NULL) {
        tcp_pcb = NULL;  // The PCB will be freed by lwIP
    }
}
// DNS found callback
// DNS found callback
void notification_dns_found_callback(const char *hostname, const ip_addr_t *ipaddr, void *arg) {
    if (ipaddr) {
        tcp_pcb = tcp_new();
        if (tcp_pcb) {
            tcp_arg(tcp_pcb, NULL);
            tcp_recv(tcp_pcb, tcp_recv_callback);
            tcp_err(tcp_pcb, tcp_error_callback);

            // Connect to IFTTT server
            err_t err = tcp_connect(tcp_pcb, ipaddr, IFTTT_PORT, tcp_connected);
            if (err != ERR_OK) {
                printf("TCP connect failed: %d\n", err);
                tcp_close(tcp_pcb);
                tcp_pcb = NULL;
            }
        }
    } else {
        printf("DNS resolution failed for %s\n", hostname);
    }
}


// DNS found callback
// DNS found callback
void send_bin_full_notification(void) {
    if (!wifi_connected) {
        printf("WiFi not connected\n");
        return;
    }

    // Start DNS resolution for the IFTTT server
    ip_addr_t addr;
    err_t err = dns_gethostbyname(IFTTT_HOST, &addr, notification_dns_found_callback, NULL);

    if (err == ERR_OK) {
        // Address cached, call callback directly
        notification_dns_found_callback(IFTTT_HOST, &addr, NULL);
    } else if (err != ERR_INPROGRESS) {
        printf("DNS resolution failed\n");
    }
}


bool notification_init(const char* ssid, const char* password) {
    // Initialize WiFi
    if (cyw43_arch_init()) {
        printf("Failed to initialize CYW43 architecture\n");
        return false;
    }
    
    // Connect to WiFi
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to WiFi\n");
        return false;
    }
    
    printf("Connected to WiFi\n");
    wifi_connected = true;
    return true;
}

void notification_service(void) {
    cyw43_arch_poll();
    sleep_ms(10);
}

unsigned int lwip_port_rand(void) {
    return get_rand_32();
}
