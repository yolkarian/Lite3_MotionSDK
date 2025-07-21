#include "receiver.h"
#include "receiver.hpp"
#include <functional>

/// @brief Structure to hold callback and user data
struct CallbackContext {
    ReceiverCallback callback;
    void* user_data;
};

/// @brief Create a new Receiver object
ReceiverHandle* Receiver_create() {
    try {
        Receiver* receiver = new Receiver();
        return reinterpret_cast<ReceiverHandle*>(receiver);
    } catch (...) {
        return nullptr;
    }
}

/// @brief Destroy a Receiver object
void Receiver_destroy(ReceiverHandle* handle) {
    if (handle) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        delete receiver;
    }
}

/// @brief Start the receiving process
void Receiver_startWork(ReceiverHandle* handle) {
    if (handle) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        receiver->StartWork();
    }
}

/// @brief Register a callback function
void Receiver_registerCallback(ReceiverHandle* handle, ReceiverCallback callback, void* user_data) {
    if (handle && callback) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        // Create a context to store callback and user data
        CallbackContext* context = new CallbackContext{callback, user_data};
        // Wrap C callback in std::function
        receiver->RegisterCallBack([context](int instruction) {
            context->callback(instruction, context->user_data);
        });
    }
}

/// @brief Get the received robot state data
RobotData* Receiver_getState(ReceiverHandle* handle) {
    if (handle) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        return &receiver->GetState();
    }
    return nullptr;
}