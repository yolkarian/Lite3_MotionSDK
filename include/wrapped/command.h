#ifndef COMMAND_WRAPPED_H_
#define COMMAND_WRAPPED_H_

#include <stdint.h>
#include <stddef.h>

#define COMMAND_DATA_BUFFER_SIZE 1024

typedef enum {
    COMMAND_TYPE_SINGLE_VALUE = 0,
    COMMAND_TYPE_MULTI_VALUE = 1
} CommandType;

#ifndef COMMAND_H_
#define COMMAND_H_

typedef struct {
    uint32_t code;
    union {
        uint32_t value;
        uint32_t parameters_size;
    };
    struct {
        uint32_t type : 8;   ///< Command type (0: single, 1: multiple)
        uint32_t count : 24; ///< Sequence number
    };
} EthCommand;

typedef struct {
    EthCommand command;
    char data_buffer[COMMAND_DATA_BUFFER_SIZE];
} CommandMessage;

#endif

typedef void* CommandHandle;

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Create a Command with a single value
/// @param command_code The command code
/// @param command_value The command value
/// @return Handle to the created Command, or NULL on failure
CommandHandle Command_CreateWithValue(uint32_t command_code, int32_t command_value);

/// @brief Create a Command with parameters
/// @param command_code The command code
/// @param parameters_size Size of the parameters
/// @param parameters Pointer to the parameters
/// @return Handle to the created Command, or NULL on failure
CommandHandle Command_CreateWithParameters(uint32_t command_code, size_t parameters_size, void* parameters);

/// @brief Destroy a Command
/// @param handle Handle to the Command
void Command_Destroy(CommandHandle handle);

/// @brief Get the command code
/// @param handle Handle to the Command
/// @return The command code
uint32_t Command_GetCode(CommandHandle handle);

/// @brief Get the command value
/// @param handle Handle to the Command
/// @return The command value
int32_t Command_GetValue(CommandHandle handle);

/// @brief Get the command parameters size
/// @param handle Handle to the Command
/// @return The size of the parameters
size_t Command_GetParametersSize(CommandHandle handle);

/// @brief Get the command parameters
/// @param handle Handle to the Command
/// @return Pointer to the parameters
void* Command_GetParameters(CommandHandle handle);

/// @brief Convert Command to string representation
/// @param handle Handle to the Command
/// @param buffer Output buffer for the string
/// @param buffer_size Size of the output buffer
/// @return 0 on success, non-zero on failure
// int Command_ToString(CommandHandle handle, char* buffer, size_t buffer_size); 
// NOTE: not implemented yet. Cannot call operator<<(std::ostream&, Command&)

#ifdef __cplusplus
}
#endif

#endif // COMMAND_WRAPPER_H_