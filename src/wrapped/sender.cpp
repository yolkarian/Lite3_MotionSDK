#include "sender.h"
#include "sender_.h"
#include <string>

extern "C" {

SenderHandle Sender_Create() {
    Sender* sender = new Sender("192.168.1.120", 43893);
    return static_cast<SenderHandle>(sender);
}

SenderHandle Sender_CreateWithIpPort(const char* ip, uint16_t port) {
    Sender* sender = new Sender(ip ? std::string(ip) : "192.168.1.120", port);
    return static_cast<SenderHandle>(sender);
}

void Sender_Destroy(SenderHandle handle) {
    if (handle) {
        delete static_cast<Sender*>(handle);
    }
}

void Sender_SendCmd(SenderHandle handle, const RobotCmd* robot_cmd) {
    if (handle && robot_cmd) {
        Sender* sender = static_cast<Sender*>(handle);
        sender->SendCmd(const_cast<RobotCmd&>(*robot_cmd));
    }
}

void Sender_ControlGet(SenderHandle handle, uint32_t mode) {
    if (handle) {
        static_cast<Sender*>(handle)->ControlGet(mode);
    }
}

void Sender_AllJointBackZero(SenderHandle handle) {
    if (handle) {
        static_cast<Sender*>(handle)->AllJointBackZero();
    }
}

void Sender_RobotStateInit(SenderHandle handle) {
    if (handle) {
        static_cast<Sender*>(handle)->RobotStateInit();
    }
}

void Sender_SetCmd(SenderHandle handle, uint32_t code, uint32_t value) {
    if (handle) {
        static_cast<Sender*>(handle)->SetCmd(code, value);
    }
}

} // extern "C"