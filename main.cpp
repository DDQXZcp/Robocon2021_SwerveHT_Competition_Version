#include "mbed.h"
//#include "platform/mbed_thread.h"
#include "swerve.h"

Thread receiver_thread;
Thread swerve_thread;
Semaphore one_slot(1);

CAN can0(PA_11, PA_12, 1000000);
CAN can1(PB_12, PB_13, 1000000);


struct comm{
        volatile float rpm = 0;

        volatile float pos = 0;
        
        volatile float rotationL = 0;
        volatile float rotationR = 0;
        
        volatile bool button1;
        volatile bool button2;
        volatile bool button3;
        volatile bool button4;
        
        volatile bool turnL;
        volatile bool turnR;

} _comm;

void reciever_task(){
    BufferedSerial *DS4BT_BS = new BufferedSerial(PA_9, PA_10);
    receiver _receiver(DS4BT_BS);
    
    while(1){
     _receiver.receiver_read();

    _comm.rpm = _receiver.rpm; 
    _comm.pos = _receiver.pos;
    _comm.rotationL = _receiver.rotationL;
    _comm.rotationR = _receiver.rotationR;
    _comm.button1 =_receiver.button1;
    _comm.button2 =_receiver.button2;
    _comm.button3 =_receiver.button3;
    _comm.button4 =_receiver.button4;
    _comm.turnL =_receiver.turnL;
    _comm.turnR =_receiver.turnR;
    }

}

void swerve_task(){
    swerve _swerve(&can0,&can1);
    while(1){
        _swerve.button1 = (int8_t)_comm.button1;
        _swerve.button2 = (int8_t)_comm.button2;
        _swerve.button3 = (int8_t)_comm.button3;
        _swerve.button4 = (int8_t)_comm.button4;
        _swerve.rpm = _comm.rpm; 
        _swerve.pos = _comm.pos;
        _swerve.turnL = _comm.turnL;
        _swerve.turnR = _comm.turnR;  
        _swerve.rotation = _comm.rotationR - _comm.rotationL;
        _swerve.mSpeed1 = 5000;
        _swerve.mSpeed2 = 5000;
        _swerve.mSpeed3 = 5000;
        _swerve.mSpeed4 = 5000;
        _swerve.swerve_write();
    }
}


int main(){
    receiver_thread.start(callback(reciever_task));
  swerve_thread.start(callback(swerve_task));
}

