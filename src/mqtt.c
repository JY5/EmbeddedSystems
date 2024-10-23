// #include "pico/cyw43_arch.h"
// #include "MQTTClient.h"
// #include "mqtt.h"
// #include <stdio.h>
// #include <string.h>

// #define MQTT_HOST "your-mqtt-broker-address"  // Replace with your broker's address
// #define MQTT_PORT 1883  // MQTT port (default is 1883)
// #define CLIENT_ID "pico_client"  // Unique client ID
// #define TOPIC_PUBLISH "pico/button"  // Topic to publish
// #define TOPIC_SUBSCRIBE "pico/feedback"  // Topic to subscribe
// #define QOS0 0  // QoS level 0

// static MQTTClient client;

// // Handle received MQTT messages and control LEDs
// void mqtt_message_arrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
//     char msg[100];
//     strncpy(msg, (char *)message->payload, message->payloadlen);
//     msg[message->payloadlen] = '\0';  // Null-terminate the message

//     printf("Received message: %s\n", msg);

//     // Extract GPIO pin values from context
//     uint green_led_pin = ((uint *)context)[0];
//     uint red_led_pin = ((uint *)context)[1];

//     // Check if the message is "correct" or "incorrect"
//     if (strcmp(msg, "correct") == 0) {
//         gpio_put(green_led_pin, true);  // Turn on green LED
//         gpio_put(red_led_pin, false);   // Turn off red LED
//     } else if (strcmp(msg, "incorrect") == 0) {
//         gpio_put(red_led_pin, true);    // Turn on red LED
//         gpio_put(green_led_pin, false); // Turn off green LED
//     }

//     // Free the message and topic name allocated by the library
//     MQTTClient_freeMessage(&message);
//     MQTTClient_free(topicName);
// }

// // MQTT connection setup
// void mqtt_connect(uint green_led_pin, uint red_led_pin) {
//     MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
//     int rc;

//     MQTTClient_create(&client, MQTT_HOST, CLIENT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

//     conn_opts.keepAliveInterval = 20;
//     conn_opts.cleansession = 1;

//     if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
//         printf("Failed to connect to MQTT broker, return code %d\n", rc);
//         return;
//     }

//     printf("Connected to MQTT broker.\n");

//     // Subscribe to the feedback topic with LED pins as context
//     uint led_pins[2] = {green_led_pin, red_led_pin};
//     MQTTClient_setCallbacks(client, led_pins, NULL, mqtt_message_arrived, NULL);

//     if ((rc = MQTTClient_subscribe(client, TOPIC_SUBSCRIBE, QOS0)) != MQTTCLIENT_SUCCESS) {
//         printf("Failed to subscribe to topic, return code %d\n", rc);
//     }
// }

// // Publish a message to the MQTT broker
// void mqtt_publish(const char *message) {
//     MQTTClient_message pubMessage = MQTTClient_message_initializer;
//     pubMessage.payload = (void *)message;
//     pubMessage.payloadlen = strlen(message);
//     pubMessage.qos = QOS0;
//     pubMessage.retained = 0;

//     MQTTClient_deliveryToken token;
//     int rc = MQTTClient_publishMessage(client, TOPIC_PUBLISH, &pubMessage, &token);

//     if (rc != MQTTCLIENT_SUCCESS) {
//         printf("Failed to publish message, return code %d\n", rc);
//     } else {
//         MQTTClient_waitForCompletion(client, token, 1000L);
//         printf("Message published: %s\n", message);
//     }
// }

// // Check for MQTT messages (accepts GPIO pins for LEDs)
// void mqtt_check_messages() {
//     MQTTClient_yield();
// }

// // Function to connect to Wi-Fi
// void connect_wifi(const char *ssid, const char *password) {
//     if (cyw43_arch_init() != 0) {
//         printf("Failed to initialize Wi-Fi module.\n");
//         return;
//     }
//     if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
//         printf("Wi-Fi connection failed!\n");
//         return;
//     }
//     printf("Connected to Wi-Fi.\n");
// }
