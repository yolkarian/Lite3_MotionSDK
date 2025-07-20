#include "udp_socket.h"
#include "udpsocket.hpp"
#include <string>

// Wrapper struct to hold UDPSocket instance and user data
struct UDPSocketHandle {
    ::UDPSocket* impl; // Pointer to the original C++ UDPSocket
    void* on_message_user_data; // User data for onMessageReceived callback
    void* on_raw_message_user_data; // User data for onRawMessageReceived callback
};

// Helper to convert C++ onError to C on_error
static void wrap_on_error(int error_code, const std::string& error_message, UDPSocket_OnError on_error) {
    if (on_error) {
        on_error(error_code, error_message.c_str());
    }
}

// Create a UDP socket
UDPSocketHandle* UDPSocket_Create(int socket_id, UDPSocket_OnError on_error, int use_connect) {
    UDPSocketHandle* wrapper = new UDPSocketHandle;
    wrapper->impl = new ::UDPSocket(use_connect != 0, 
        [on_error](int error_code, const std::string& error_message) {
            wrap_on_error(error_code, error_message, on_error);
        }, 
        socket_id);
    wrapper->on_message_user_data = nullptr;
    wrapper->on_raw_message_user_data = nullptr;
    return wrapper;
}

// Destroy a UDP socket
void UDPSocket_Destroy(UDPSocketHandle* socket) {
    if (socket) {
        delete socket->impl;
        delete socket;
    }
}

// Send data to a specific host and port (connectionless)
void UDPSocket_SendTo(UDPSocketHandle* socket, const char* bytes, size_t bytes_length, const char* host, uint16_t port, UDPSocket_OnError on_error) {
    if (socket && socket->impl) {
        socket->impl->SendTo(bytes, bytes_length, host, port, 
            [on_error](int error_code, const std::string& error_message) {
                wrap_on_error(error_code, error_message, on_error);
            });
    }
}

// Send string to a specific host and port (connectionless)
void UDPSocket_SendToString(UDPSocketHandle* socket, const char* message, const char* host, uint16_t port, UDPSocket_OnError on_error) {
    if (socket && socket->impl && message) {
        socket->impl->SendTo(message, host, port, 
            [on_error](int error_code, const std::string& error_message) {
                wrap_on_error(error_code, error_message, on_error);
            });
    }
}

// Connect to a host and port (for connection-oriented communication)
void UDPSocket_Connect(UDPSocketHandle* socket, const char* host, uint16_t port, UDPSocket_OnError on_error) {
    if (socket && socket->impl && host) {
        socket->impl->Connect(host, port, 
            [on_error](int error_code, const std::string& error_message) {
                wrap_on_error(error_code, error_message, on_error);
            });
    }
}

void UDPSocket_ConnectIP(UDPSocketHandle* socket, uint32_t ipv4, uint16_t port, UDPSocket_OnError on_error) {
    if (socket && socket->impl) {
        socket->impl->Connect(ipv4, port, 
            [on_error](int error_code, const std::string& error_message) {
                wrap_on_error(error_code, error_message, on_error);
            });
    }
}

// Send data (connection-oriented)
int UDPSocket_Send(UDPSocketHandle* socket, const char* bytes, size_t bytes_length) {
    if (socket && socket->impl) {
        return socket->impl->Send(bytes, bytes_length);
    }
    return -1;
}

int UDPSocket_SendString(UDPSocketHandle* socket, const char* message) {
    if (socket && socket->impl && message) {
        return socket->impl->Send(message);
    }
    return -1;
}

// Set callback for receiving messages
void UDPSocket_SetOnMessageReceived(UDPSocketHandle* socket, UDPSocket_OnMessageReceived callback, void* user_data) {
    if (socket && socket->impl) {
        socket->on_message_user_data = user_data;
        if (callback) {
            socket->impl->onMessageReceived = [callback, user_data](const std::string& message, const std::string& host, uint16_t port) {
                callback(message.c_str(), host.c_str(), port, user_data);
            };
        } else {
            socket->impl->onMessageReceived = nullptr;
        }
    }
}

// Set callback for receiving raw messages
void UDPSocket_SetOnRawMessageReceived(UDPSocketHandle* socket, UDPSocket_OnRawMessageReceived callback, void* user_data) {
    if (socket && socket->impl) {
        socket->on_raw_message_user_data = user_data;
        if (callback) {
            socket->impl->onRawMessageReceived = [callback, user_data](const char* buffer, int length, const std::string& host, uint16_t port) {
                callback(buffer, length, host.c_str(), port, user_data);
            };
        } else {
            socket->impl->onRawMessageReceived = nullptr;
        }
    }
}
