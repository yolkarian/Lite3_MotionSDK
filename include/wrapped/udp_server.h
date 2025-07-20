#ifndef UDP_SERVER_WRAPPED_H
#define UDP_SERVER_WRAPPED_H

#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

// Opaque pointer to avoid naming conflict with C++ UDPServer class
typedef struct UDPServerHandle UDPServerHandle ;

// Callback type for error handling
typedef void (*UDPServer_OnError)(int errorCode, const char* errorMessage);

// Create and destroy UDPServerHandle
UDPServerHandle * UDPServer_create();
void UDPServer_destroy(UDPServerHandle * server);

// Bind functions
void UDPServer_bind(UDPServerHandle * server, const char* ipv4, uint16_t port, UDPServer_OnError onError);
void UDPServer_bind_port(UDPServerHandle* server, int port, UDPServer_OnError onError);

// Set broadcast option
void UDPServer_set_broadcast(UDPServerHandle* server, UDPServer_OnError onError);

#ifdef __cplusplus
}
#endif
#endif // UDP_SERVER_WRAPPER_H