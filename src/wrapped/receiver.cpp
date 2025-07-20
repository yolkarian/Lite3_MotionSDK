#include "receiver.h"
#include "receiver_.h"
#include <functional>

/// @brief Structure to hold callback and user data
struct CallbackContext {
    ReceiverCallback callback;
    void* user_data;
};

/// @brief Create a new Receiver object
ReceiverHandle* Receiver_Create() {
    try {
        Receiver* receiver = new Receiver();
        return reinterpret_cast<ReceiverHandle*>(receiver);
    } catch (...) {
        return nullptr;
    }
}

/// @brief Destroy a Receiver object
void Receiver_Destroy(ReceiverHandle* handle) {
    if (handle) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        delete receiver;
    }
}

/// @brief Start the receiving process
void Receiver_StartWork(ReceiverHandle* handle) {
    if (handle) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        receiver->StartWork();
    }
}

/// @brief Register a callback function
void Receiver_RegisterCallback(ReceiverHandle* handle, ReceiverCallback callback, void* user_data) {
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
RobotData* Receiver_GetState(ReceiverHandle* handle) {
    if (handle) {
        Receiver* receiver = reinterpret_cast<Receiver*>(handle);
        return &receiver->GetState();
    }
    return nullptr;
}