#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"
#include "lwip/timeouts.h"
#include "hardware/adc.h"
#include "microphone.h"
#include <stdio.h>

#define LWIP_MQTT_DEBUG LWIP_DBG_ON



// // Wi-Fi credentials
// #define WIFI_SSID       "SINGTEL-DGH8"
// #define WIFI_PASSWORD   "wvk9h4f84c"

#define WIFI_SSID       "Pixel_2164"
#define WIFI_PASSWORD   "twerkdatass"

// MQTT Broker details
#define MQTT_BROKER_IP  "192.168.8.43"  // Replace with your broker's IP
#define MY_MQTT_PORT    1883            // Renamed to avoid conflict

// GPIO Definitions
#define MIC_ADC_GPIO    26    // GPIO pin for microphone (ADC channel 0)

// Function prototypes
void init_gpio(void);
void init_wifi(void);
void connect_to_mqtt_broker(void);

// MQTT callbacks
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void mqtt_sub_request_cb(void *arg, err_t result);
void mqtt_pub_request_cb(void *arg, err_t result);
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);

// Global variables
volatile bool mqtt_connected = false;
mqtt_client_t *mqtt_client;

void init_gpio(void) {
    // Initialize your GPIO pins here
    // Example for initializing LEDs and button
    gpio_init(15);  // GREEN_LED_GPIO
    gpio_set_dir(15, GPIO_OUT);
    gpio_put(15, false);

    gpio_init(16);  // RED_LED_GPIO
    gpio_set_dir(16, GPIO_OUT);
    gpio_put(16, false);

    gpio_init(14);  // BUTTON_GPIO
    gpio_set_dir(14, GPIO_IN);
    gpio_pull_up(14);
}

void init_wifi(void) {
    printf("Starting Wi-Fi initialization...\n");

    if (cyw43_arch_init()) {
        printf("Failed to initialize Wi-Fi\n");
        // gpio_put(15, false);
        // while (1) tight_loop_contents(); // Stay in a loop if Wi-Fi fails
    } 
    printf("Wi-Fi initialized successfully!\n");
    // gpio_put(16, true);

    cyw43_arch_enable_sta_mode();
    printf("Wi-Fi station mode enabled\n");

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect to Wi-Fi\n");
        while (1) tight_loop_contents();
    }
    printf("Connected to Wi-Fi\n");
    printf("Pico W IP address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));
}

void connect_to_mqtt_broker(void) {
    ip_addr_t broker_ip;
    ip4addr_aton(MQTT_BROKER_IP, &broker_ip);

    mqtt_client = mqtt_client_new();
    if (mqtt_client == NULL) {
        printf("Failed to create MQTT client\n");
        return;
    }

    struct mqtt_connect_client_info_t ci;
    memset(&ci, 0, sizeof(ci));
    ci.client_id = "pico_client_unique";
    ci.keep_alive = 120;

    printf("Connecting to MQTT broker...\n");
    err_t err = mqtt_client_connect(mqtt_client, &broker_ip, MY_MQTT_PORT, mqtt_connection_cb, NULL, &ci);
    
    if (err != ERR_OK) {
        printf("MQTT connection failed with error: %d\n", err);
    }
}


// void connect_to_mqtt_broker(void) {
//     ip_addr_t broker_ip;
//     ip4addr_aton(MQTT_BROKER_IP, &broker_ip);

//     mqtt_client = mqtt_client_new();
//     if (mqtt_client == NULL) {
//         printf("Failed to create MQTT client\n");
//         while (1) tight_loop_contents();
//     }

//     mqtt_set_inpub_callback(mqtt_client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, NULL);

//     struct mqtt_connect_client_info_t ci;
//     memset(&ci, 0, sizeof(ci));
//     ci.client_id = "pico_client";
//     ci.keep_alive = 60;

//     printf("Connecting to MQTT broker...\n");
//     mqtt_client_connect(mqtt_client, &broker_ip, MY_MQTT_PORT, mqtt_connection_cb, NULL, &ci);
// }

extern void ping_send(const ip_addr_t *addr);

int main() {
    stdio_init_all();
    sleep_ms(10000);
    printf("Serial initialized\n");


    // Initialize Wi-Fi
    printf("Initializing Wifi\n");
    init_wifi();

    // Test if we can ping the MQTT broker
    ip_addr_t broker_ip;
    ip4addr_aton(MQTT_BROKER_IP, &broker_ip);
    ping_send(&broker_ip);  // Use the custom ping function

    // Initialize GPIO pins and microphone
    init_gpio();
    init_microphone(MIC_ADC_GPIO);

    // Connect to MQTT broker
    connect_to_mqtt_broker();

    while (1) {

        sys_check_timeouts();  // Process LWIP timeouts

        // Check if connected to MQTT broker before publishing
        if (mqtt_connected) {
            uint16_t audio_sample = get_audio_sample();
            printf("Audio sample: %u\n", audio_sample);

            char message[64];
            snprintf(message, sizeof(message), "%u", audio_sample);

            err_t err = mqtt_publish(mqtt_client, "audio/samples", message, strlen(message), 0, 0, mqtt_pub_request_cb, NULL);
            if (err != ERR_OK) {
                printf("Publish err: %d\n", err);
            }
        }

        sleep_ms(100);  // Adjust as needed
    }

    cyw43_arch_deinit();
    return 0;
}

// MQTT connection callback
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("Connected to MQTT broker\n");
        mqtt_connected = true;

        // Subscribe to topics if needed
        err_t err = mqtt_subscribe(client, "test/topic", 0, mqtt_sub_request_cb, NULL);
        if (err != ERR_OK) {
            printf("Subscribe err: %d\n", err);
        }
    } else {
        printf("Disconnected from MQTT broker, reason: %d\n", status);
        mqtt_connected = false;
    }
}

void mqtt_sub_request_cb(void *arg, err_t result) {
    if (result == ERR_OK) {
        printf("Subscription successful\n");
    } else {
        printf("Subscription failed\n");
    }
}

void mqtt_pub_request_cb(void *arg, err_t result) {
    if (result != ERR_OK) {
        printf("Publish result: %d\n", result);
    }
}

void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
    printf("Incoming publish at topic %s with total length %u\n", topic, tot_len);
}

void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
    printf("Incoming data: %.*s\n", len, data);
}
