#ifndef UDP_SOCKET_WRAPPED_H
#define UDP_SOCKET_WRAPPED_H
#include "stdint.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointer to UDPSocket implementation
typedef struct UDPSocketHandle UDPSocketHandle;

// Callback types for message received and error handling
typedef void (*UDPSocket_OnMessageReceived)(const char* message, const char* host, uint16_t port, void* user_data);
typedef void (*UDPSocket_OnRawMessageReceived)(const char* buffer, int length, const char* host, uint16_t port, void* user_data);
typedef void (*UDPSocket_OnError)(int error_code, const char* error_message);

// Create a UDP socket
UDPSocketHandle* UDPSocket_Create(int socket_id, UDPSocket_OnError on_error, int use_connect);

// Destroy a UDP socket
void UDPSocket_Destroy(UDPSocketHandle* socket);

// Send data to a specific host and port (connectionless)
void UDPSocket_SendTo(UDPSocketHandle* socket, const char* bytes, size_t bytes_length, const char* host, uint16_t port, UDPSocket_OnError on_error);

// Send string to a specific host and port (connectionless)
void UDPSocket_SendToString(UDPSocketHandle* socket, const char* message, const char* host, uint16_t port, UDPSocket_OnError on_error);

// Connect to a host and port (for connection-oriented communication)
void UDPSocket_Connect(UDPSocketHandle* socket, const char* host, uint16_t port, UDPSocket_OnError on_error);
void UDPSocket_ConnectIP(UDPSocketHandle* socket, uint32_t ipv4, uint16_t port, UDPSocket_OnError on_error);

// Send data (connection-oriented, requires Connect first)
int UDPSocket_Send(UDPSocketHandle* socket, const char* bytes, size_t bytes_length);
int UDPSocket_SendString(UDPSocketHandle* socket, const char* message);

// Set callback for receiving messages
void UDPSocket_SetOnMessageReceived(UDPSocketHandle* socket, UDPSocket_OnMessageReceived callback, void* user_data);

// Set callback for receiving raw messages
void UDPSocket_SetOnRawMessageReceived(UDPSocketHandle* socket, UDPSocket_OnRawMessageReceived callback, void* user_data);


#ifdef __cplusplus
}
#endif

#endif // UDP_SOCKET_WRAPPER_H