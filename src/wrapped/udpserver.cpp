#include "udpserver.h"
#include "udpserver.hpp" // Original C++ header
#include <string>

// Implementation of UDPServer as an opaque struct
struct UDPServerHandle {
    UDPServerHandle() : impl(new ::UDPServer()) {}
    ~UDPServerHandle() { delete impl; }
    ::UDPServer* impl; // Pointer to actual C++ UDPServer object
};

UDPServerHandle* UDPServer_create() {
    return new UDPServerHandle();
}

void UDPServer_destroy(UDPServerHandle* server) {
    if (server) {
        delete server;
    }
}

void UDPServer_bind(UDPServerHandle* server, const char* ipv4, uint16_t port, UDPServer_OnError onError) {
    if (!server || !ipv4) {
        if (onError) {
            onError(EINVAL, "Invalid server or IP address.");
        }
        return;
    }

    server->impl->Bind(
        std::string(ipv4),
        port,
        [onError](int errorCode, std::string errorMessage) {
            if (onError) {
                onError(errorCode, errorMessage.c_str());
            }
        }
    );
}

void UDPServer_bind_port(UDPServerHandle* server, int port, UDPServer_OnError onError) {
    if (!server || port < 0 || port > 65535) {
        if (onError) {
            onError(EINVAL, "Invalid server or port number.");
        }
        return;
    }

    server->impl->Bind(
        port,
        [onError](int errorCode, std::string errorMessage) {
            if (onError) {
                onError(errorCode, errorMessage.c_str());
            }
        }
    );
}

void UDPServer_set_broadcast(UDPServerHandle* server, UDPServer_OnError onError) {
    if (!server) {
        if (onError) {
            onError(EINVAL, "Invalid server.");
        }
        return;
    }

    server->impl->setBroadcast(
        [onError](int errorCode, std::string errorMessage) {
            if (onError) {
                onError(errorCode, errorMessage.c_str());
            }
        }
    );
}