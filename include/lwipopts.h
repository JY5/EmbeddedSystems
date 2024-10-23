#ifndef LWIPOPTS_H
#define LWIPOPTS_H

// Basic lwIP options
#define NO_SYS                  1  // We are not using an RTOS
#define LWIP_SOCKET             0  // We are not using sockets
#define LWIP_NETCONN            0  // Disable Netconn API (sockets API alternative)
#define LWIP_TCP                1  // Enable TCP
#define LWIP_DNS                1  // Enable DNS

#define MEM_ALIGNMENT           4  // Memory alignment for the architecture
#define MEM_SIZE                (2 * 1024)  // Set memory size (adjust as needed)

// Other options can be added here as needed for your application

#endif // LWIPOPTS_H
