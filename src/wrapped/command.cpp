/// @file command_wrapper.cpp
/// @brief Implementation of C-compatible wrapper for Command class
/// @version 0.1
/// @date 2025-07-20
/// @copyright Copyright (c) 2025

#include "command.hpp"
#include "command.h" // Original header with Command class
#include <sstream>
#include <cstring>

extern "C" {

CommandHandle Command_CreateWithValue(uint32_t command_code, int32_t command_value) {
    try {
        Command* cmd = new Command(command_code, command_value);
        return static_cast<CommandHandle>(cmd);
    } catch (...) {
        return nullptr;
    }
}

CommandHandle Command_CreateWithParameters(uint32_t command_code, size_t parameters_size, void* parameters) {
    try {
        Command* cmd = new Command(command_code, parameters_size, parameters);
        return static_cast<CommandHandle>(cmd);
    } catch (...) {
        return nullptr;
    }
}

void Command_Destroy(CommandHandle handle) {
    if (handle) {
        delete static_cast<Command*>(handle);
    }
}

uint32_t Command_GetCode(CommandHandle handle) {
    if (!handle) return 0;
    Command* cmd = static_cast<Command*>(handle);
    return cmd->GetCommandCode().to_ulong();
}

int32_t Command_GetValue(CommandHandle handle) {
    if (!handle) return 0;
    Command* cmd = static_cast<Command*>(handle);
    return cmd->GetCommandValue();
}

size_t Command_GetParametersSize(CommandHandle handle) {
    if (!handle) return 0;
    Command* cmd = static_cast<Command*>(handle);
    return cmd->GetCommandParametersSize();
}

void* Command_GetParameters(CommandHandle handle) {
    if (!handle) return nullptr;
    Command* cmd = static_cast<Command*>(handle);
    return cmd->GetCommandParameters();
}

// NOTE: not implemented yet. Cannot call operator<<(std::ostream&, Command&)
// int Command_ToString(CommandHandle handle, char* buffer, size_t buffer_size) {
//     if (!handle || !buffer || buffer_size == 0) return -1;

//     Command* cmd = static_cast<Command*>(handle);
//     std::stringstream ss;
//     ss << (*cmd);
//     std::string result = ss.str();

//     if (result.size() >= buffer_size) {
//         return -2; // Buffer too small
//     }

//     strncpy(buffer, result.c_str(), buffer_size);
//     buffer[buffer_size - 1] = '\0'; // Ensure null-termination
//     return 0;
// }

} // extern "C"