#include <stdint.h>
#include "mbed.h"
#include "receiver.h"
#include "datatypes.h"

#define VelDir_id 0x50
#define Sw_id 0x51
#define Rotate_id 0x52

CANMessage can_receive_msg;

receiver::receiver(BufferedSerial *_BS){
    _BS->set_baud(115200);
    DS4_BT_1 = new DS4_BT_Serial_Host_Shield(_BS);
}

float receiver::utils_fast_atan2(float y, float x) {
	float abs_y = fabsf(y) + 1e-20; // kludge to prevent 0/0 condition
	float angle;

	if (x >= 0) {
		float r = (x - abs_y) / (x + abs_y);
		float rsq = r * r;
		angle = ((0.1963 * rsq) - 0.9817) * r + (M_PI / 4.0);
	} else {
		float r = (x + abs_y) / (abs_y - x);
		float rsq = r * r;
		angle = ((0.1963 * rsq) - 0.9817) * r + (3.0 * M_PI / 4.0);
	}

	if (y < 0) {
		return(-angle);
	} else {
		return(angle);
	}
}



/////CAN Send is Triggered when Receiving CAN Message/////
void receiver::receiver_read()//CAN      中断接收程序  
{
	DS4_BT_1->getPacket();
    M_PI = 3.14159265359;
    x_dir = (float)DS4_BT_1->DS4_Input.Rstick_x / 127.0;
    y_dir = (float)DS4_BT_1->DS4_Input.Rstick_y / 127.0;
    sq = sqrt(x_dir*x_dir+y_dir*y_dir);
    pos = utils_fast_atan2(x_dir,y_dir)/M_PI*180;
    rpm = DS4_BT_1->DS4_Input.Lstick_y/127.0*7000;
    if(sq<0.3){
        pos = 0;
        }
//    if(sq > 0.5){
//        pos = utils_fast_atan2(x_dir,y_dir)/M_PI*180;
//        pos_past = pos;
//        }
//    else{
//    	pos = pos_past;
//    	}
    turnL = DS4_BT_1->DS4_Input.L1;	
    turnR = DS4_BT_1->DS4_Input.R1;
    button1 = DS4_BT_1->DS4_Input.Triangle;
    button2 = DS4_BT_1->DS4_Input.Circle;
    button3 = DS4_BT_1->DS4_Input.Square;
    button4 = DS4_BT_1->DS4_Input.Cross;
    rotationL = (float)DS4_BT_1->DS4_Input.L2_Trigger / 256.0;
    rotationR = (float)DS4_BT_1->DS4_Input.R2_Trigger / 256.0;

}


    

