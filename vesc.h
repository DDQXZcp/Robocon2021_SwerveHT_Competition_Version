#include "mbed.h"
#include "datatypes.h"

class vesc
{
public:
    //Change to vesc_init to replace constructor    
    void vesc_init(int CAN_ID, CAN* _CAN);
    void stop();
    
    void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index);
    bool sendPacket(uint32_t id, uint8_t packet[], int32_t len);
    void SetDuty(float duty);
    void crossbow(float pos);
    void brake(float brake_current);
    
    void comm_can_set_duty(float duty);
    void comm_can_set_current(float current);
    void comm_can_set_current_brake(float current);
    void comm_can_set_rpm(float rpm);
    void comm_can_set_pos(float pos);
    
    int controller_id;
    CAN* CAN0;
    long unsigned int rxId;
    unsigned char rxBuf[8];
    char msgString[128];
    char display_buffer[8]; 
};
