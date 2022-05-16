#include "mbed.h"
#include "datatypes.h"
#include "receiver.h"
#include "vesc.h"

class swerve
{
public:    
    swerve(CAN* _CANA, CAN* _CANB);
    void stop();
    
    vesc _vesc1;
    vesc _vesc2;
    vesc _vesc3;
    vesc _vesc4;
    vesc _vesc5;
    vesc _vesc6;
    vesc _vesc7;
    vesc _vesc8;
    
    void swerve_init();
    void swerve_write();
    CAN* CANA;
    CAN* CANB;
    
    int32_t receive_cnt = 0;
    
    float prev_pos;
    int32_t loop_cnt = 0;
    float angle1;
    float angle2;
    float angle3;
    float angle4;
    
    float rpm;
    float pos;
    
    double wSpeed1;
    double wAngle1;
    double wSpeed2;
    double wAngle2;
    double wSpeed3;
    double wAngle3;
    double wSpeed4;
    double wAngle4;
    double mSpeed1;
    double mAngle1;
    double mSpeed2;
    double mAngle2;
    double mSpeed3;
    double mAngle3;
    double mSpeed4;
    double mAngle4;
    
    double pre_wSpeed1;
    double pre_wSpeed2;
    double pre_wSpeed3;
    double pre_wSpeed4;
    
    float GEAR_RATIO = 7;
    float VESC_MAX_RPM = 5000;
    
    double speed_x;
    double speed_y;
    double rotation_x;
    double rotation_y;
    
    int8_t button1;
    int8_t prev_button1;
    int8_t button1_state;
    int8_t button2;
    int8_t prev_button2;
    int8_t button2_state;
    int8_t button3;
    int8_t prev_button3;
    int8_t button3_state;
    int8_t button4;
    int8_t prev_button4;
    int8_t button4_state;
    
    int8_t turnL;
    int8_t turnR;
    
    int8_t direction_flag;//1 is forward, 0 is backward
        
    float rotation  = 0;
};

