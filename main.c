#include "robot_types.h"
#include "motionexample.h"
#include "sender.h"
#include "dr_timer.h"
#include "receiver.h"
#include <stdint.h>
#include <string.h>


bool is_message_updated_ = false; ///< Flag to check if message has been updated
/**
  * @brief Callback function to set message update flag
  * 
  * @param code The code indicating the type of message received
  */
void OnMessageUpdate(int32_t code, void* ptr){
  if(code == 0x0906){
    bool* bool_ptr = (bool*) ptr;
    *bool_ptr = true;
  }
}

int main(){
    DRTimerHandle* set_timer = DRTimer_create();
    double now_time,start_time;
    RobotCmd robot_joint_cmd;
    memset(&robot_joint_cmd, 0, sizeof(robot_joint_cmd));
  
    SenderHandle send_cmd  = Sender_create();              ///< Create send thread
    ReceiverHandle* robot_data_recv = Receiver_create();                                 ///< Create a receive resolution
    Receiver_registerCallback(robot_data_recv, OnMessageUpdate, &is_message_updated_);
    // MotionExample robot_set_up_demo;                                            ///< Demos for testing can be deleted by yourself
    RobotData *robot_data = Receiver_getState(robot_data_recv);
  
    Receiver_startWork(robot_data_recv);// robot_data_recv->StartWork();
    DRTimer_init(set_timer, 1);                   // set_timer.TimeInit(1);                                                      ///< Timer initialization, input: cycle; Unit: ms
    Sender_robotStateInit(send_cmd);// send_cmd->RobotStateInit();                                                 ///< Return all joints to zero and gain control
  
    start_time = DRTimer_getCurrentTime(set_timer);// start_time = set_timer.GetCurrentTime();                                    ///< Obtain time for algorithm usage
    getInitData(robot_data->joint_data, (double)0.000);                ///< Obtain all joint states once before each stage (action)
    
    int time_tick = 0;
    while(1){
      if (DRTimer_interrupt(set_timer) == true){                                  ///< Time interrupt flag
        continue;
      }
      now_time = DRTimer_getIntervalTime(set_timer,start_time);       ///< Get the current time
      time_tick++;
      if(time_tick < 1000){
        preStandUp(&robot_joint_cmd,now_time,robot_data);     ///< Stand up and prepare for action
      } 
      if(time_tick == 1000){
        getInitData(robot_data->joint_data,now_time);         ///< Obtain all joint states once before each stage (action)
      }
      if(time_tick >= 1000 ){
        standUp(&robot_joint_cmd,now_time,robot_data);        ///< Full stand up
      }
      if(time_tick >= 10000){
        Sender_controlGet(set_timer, ROBOT);                                            ///< Return the control right, input: ROBOT: Original algorithm control of the robot .  SDK: SDK control PS: over 50ms, no data set sent_ Send (cmd), you will lose control, you need to resend to obtain control
        break;
      }
      if(is_message_updated_){
        // send_cmd->SendCmd(robot_joint_cmd);  
      }               
      //cout << robot_data->imu.acc_x << endl;
    }
    // Unlike C++ manually destroy is needed or not
    
    Receiver_destroy(robot_data_recv);
    Sender_create(send_cmd);
    DRTimer_destroy(set_timer);
    return 0;
  } 
  