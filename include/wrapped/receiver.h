#ifndef RECEIVER_WRAPPED_H_
#define RECEIVER_WRAPPED_H_

#include "robot_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Opaque struct for the Receiver object
typedef struct ReceiverHandle ReceiverHandle;

/// @brief Callback function type for receiving data
/// @param instruction Instruction type (e.g., 0x0906)
/// @param user_data User-defined data passed to the callback
typedef void (*ReceiverCallback)(int instruction, void* user_data);

/// @brief Create a new Receiver object
/// @return Pointer to the ReceiverHandle, or NULL on failure
ReceiverHandle* Receiver_create();

/// @brief Destroy a Receiver object
/// @param handle Pointer to the ReceiverHandle
void Receiver_destroy(ReceiverHandle* handle);

/// @brief Start the receiving process
/// @param handle Pointer to the ReceiverHandle
void Receiver_startWork(ReceiverHandle* handle);

/// @brief Register a callback function
/// @param handle Pointer to the ReceiverHandle
/// @param callback Callback function to be called with received data
/// @param user_data User-defined data to pass to the callback
void Receiver_registerCallback(ReceiverHandle* handle, ReceiverCallback callback, void* user_data);

/// @brief Get the received robot state data
/// @param handle Pointer to the ReceiverHandle
/// @return Pointer to the RobotData structure
RobotData* Receiver_getState(ReceiverHandle* handle);

#ifdef __cplusplus
}
#endif

#endif // RECEIVER_WRAPPER_H_