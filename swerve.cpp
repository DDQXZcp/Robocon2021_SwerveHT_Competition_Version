#include <stdint.h>
#include "swerve.h"
#include "datatypes.h"
#include "mbed.h"
#define ROUNDNUM(x) ((int)(x + 0.5f))
#include <math.h>

#define PI 3.1415926

DigitalOut relay1(PA_13);
DigitalOut relay2(PA_14);
DigitalOut relay3(PH_1);
DigitalOut relay4(PD_2);
DigitalOut myled(PA_5);

swerve::swerve(CAN* _CANA, CAN* _CANB){
    CANA = _CANA;
    CANB = _CANB;
    CANA->frequency(1000000);
    CANB->frequency(1000000);
    _vesc1.vesc_init(70,_CANA);   
    _vesc2.vesc_init(71,_CANA);  
    _vesc3.vesc_init(72,_CANA);  
    _vesc4.vesc_init(73,_CANA);
    _vesc5.vesc_init(80,_CANA);   
    _vesc6.vesc_init(81,_CANA);  
    _vesc7.vesc_init(82,_CANA);  
    _vesc8.vesc_init(83,_CANA);
    }

void swerve::swerve_write(){

    if(rpm>0){
        direction_flag = 1;
        }
    else{
        direction_flag = 0;
        }
    rpm = abs(rpm);

    if(button1 == 0 && prev_button1 == 1){
        switch(button1_state){
        case 0:
            button1_state = 1;
            relay1 = 1;
            break;
        case 1:
            button1_state = 0;
            relay1 = 0;
        default:
            break;
        }
    }
    prev_button1= button1;

    if(button2 == 0 && prev_button2 == 1){
        switch(button2_state){
        case 0:
            button2_state = 1;
            relay2 = 1;
            break;
        case 1:
            button2_state = 0;
            relay2 = 0;
        default:
            break;
        }
    }
    prev_button2= button2;
    
    if(button3 == 0 && prev_button3 == 1){
        switch(button3_state){
        case 0:
            button3_state = 1;
            relay3 = 1;
            break;
        case 1:
            button3_state = 0;
            relay3 = 0;
        default:
            break;
        }
    }
    prev_button3= button3;
    
    if(button4 == 0 && prev_button4 == 1){
        switch(button4_state){
        case 0:
            button4_state = 1;
            relay4 = 1;
            break;
        case 1:
            button4_state = 0;
            relay4 = 0;
        default:
            break;
        }
    }
    prev_button4= button4;
        
    
    //Angle Safety check
    float theta = 180 - pos;
    float x_dif = 1*sin(theta);
    //rotate limit is to calculate the maximum (rotation vector)/(wheel vector) ratio so that it will not go through +-180 sudden change 
    float rotate_limit;
    if (pos > 135 || pos < -135){
        x_dif = abs(1*sin(theta*PI/180.0f));
        rotate_limit = sqrt(2)*x_dif;
        }
    else{rotate_limit = 1;}
    //Speed vector calculation  
    speed_y = -rpm*cos(theta*PI/180.0f);
    speed_x = rpm*sin(theta*PI/180.0f);
    //printf("speed_y: %f speed_x: %f \r", speed_y, speed_x);
    float rotation_speed = rpm*rotate_limit*0.2*rotation;
    //printf("rotation_speed: %f \r", rotation_speed);
    //wheel 1
    rotation_y = -rotation_speed/sqrt(2);
    rotation_x = rotation_speed/sqrt(2);
    //printf("rotation_y: %f rotation_x: %f \r", rotation_y, rotation_x);
    wSpeed1 = sqrt( (speed_y + rotation_y)*(speed_y + rotation_y) + (speed_x + rotation_x)*(speed_x + rotation_x) );
    wAngle1 = atan2((speed_x + rotation_x),(speed_y + rotation_y))*180/PI;
    if(wAngle1 > 179.9 || wAngle1 < -179.9){wAngle1 = 0;}
    //4zcfw yuprintf("wSpeed1: %f wAngle1: %f \r", wSpeed1, wAngle1);
    //printf("wAngle1: %f\r", wAngle1);
    //printf("wSpeed1: %f\r", wSpeed1);
    //wheel 2
    rotation_y = rotation_speed/sqrt(2);
    rotation_x = rotation_speed/sqrt(2);
    wSpeed2 = sqrt( (speed_y + rotation_y)*(speed_y + rotation_y) + (speed_x + rotation_x)*(speed_x + rotation_x) );
    wAngle2 = atan2((speed_x + rotation_x),(speed_y + rotation_y))*180/PI;
    if(wAngle2 > 179.9 || wAngle2 < -179.9){wAngle2 = 0;}
    //printf("wSpeed2: %f wAngle2: %f \r", wSpeed2, wAngle2);
    //wheel 3
    rotation_y = rotation_speed/sqrt(2);
    rotation_x = -rotation_speed/sqrt(2);
    wSpeed3 = sqrt( (speed_y + rotation_y)*(speed_y + rotation_y) + (speed_x + rotation_x)*(speed_x + rotation_x) );
    wAngle3 = atan2((speed_x + rotation_x),(speed_y + rotation_y))*180/PI;
    if(wAngle3 > 179.9 || wAngle3 < -179.9){wAngle3 = 0;}
    //printf("wSpeed3: %f wAngle3: %f \r", wSpeed3, wAngle3);
    //wheel 4
    rotation_y = -rotation_speed/sqrt(2);
    rotation_x = -rotation_speed/sqrt(2);
    wSpeed4 = sqrt( (speed_y + rotation_y)*(speed_y + rotation_y) + (speed_x + rotation_x)*(speed_x + rotation_x) );
    wAngle4 = atan2((speed_x + rotation_x),(speed_y + rotation_y))*180/PI;
    if(wAngle4 > 179.9 || wAngle4 < -179.9){wAngle4 = 0;}
    //printf("wSpeed4: %f wAngle4: %f \r", wSpeed4, wAngle4);
    
    wAngle1 = constrain(wAngle1, -180, 180);
    wAngle2 = constrain(wAngle2, -180, 180);
    wAngle3 = constrain(wAngle3, -180, 180);
    wAngle4 = constrain(wAngle4, -180, 180);
    
    angle1 = ROUNDNUM(70 - wAngle1);
    angle2 = ROUNDNUM(19 - wAngle2);
    angle3 = ROUNDNUM(250 - wAngle3);
    angle4 = ROUNDNUM(0 - wAngle4);//246 231 201
    
    _vesc5.comm_can_set_pos(angle1);//VESC_MAX_SPEED = 5000;
    _vesc6.comm_can_set_pos(angle2);
    _vesc7.comm_can_set_pos(angle3);
    _vesc8.comm_can_set_pos(angle4); 
    
    prev_pos = pos;
    
    
    //printf("pos: %f rpm: %f rotation: %f\r", pos, rpm, rotation);
    //printf("wSpeed1: %f wAngle1: %f wSpeed2: %f wAngle2: %f\r", wSpeed1, wAngle1, wSpeed2, wAngle2);
    //printf("wSpeed1: %f wAngle1: %f\r", wSpeed1, wAngle1);
    //printf("wAngle1: %f\r", wAngle1);
    //printf("pos: %f ", pos);
    //printf("rotation: %f \r", rotation);
    //printf("button: %d %d \r", button3, button4);
    //printf("\n");
    if(direction_flag == 0){
        wSpeed1 = -wSpeed1;
        wSpeed2 = -wSpeed2;
        wSpeed3 = -wSpeed3;
        wSpeed4 = -wSpeed4;
        }
    
    if(turnL == 1){
        _vesc1.comm_can_set_rpm(0);//VESC_MAX_SPEED = 5000;
        _vesc2.comm_can_set_rpm(0);
        _vesc3.comm_can_set_rpm(0);
        _vesc4.comm_can_set_rpm(0);
        }
    else{
        _vesc1.comm_can_set_rpm(ROUNDNUM(wSpeed1));//VESC_MAX_SPEED = 5000;
        _vesc2.comm_can_set_rpm(ROUNDNUM(wSpeed2));
        _vesc3.comm_can_set_rpm(ROUNDNUM(wSpeed3));
        _vesc4.comm_can_set_rpm(ROUNDNUM(-wSpeed4));
    }
/*
    _vesc1.comm_can_set_rpm(ROUNDNUM(5000));//VESC_MAX_SPEED = 5000;
    _vesc2.comm_can_set_rpm(ROUNDNUM(5000));
    _vesc3.comm_can_set_rpm(ROUNDNUM(5000));
    _vesc4.comm_can_set_rpm(ROUNDNUM(-5000));*/
    //need to pay attention to the delay
    wait_us(100);
    
}

