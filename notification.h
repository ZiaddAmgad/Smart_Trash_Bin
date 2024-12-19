#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"

// Initialize WiFi and notification system
bool notification_init(const char* ssid, const char* password);

// Send notification when bin is full
void send_bin_full_notification(void);

// Service the notification system
void notification_service(void);

// Send a Telegram message


#endif // NOTIFICATION_H