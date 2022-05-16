#include "mbed.h"
#include "vesc.h"

unsigned char len = 0;

//https://github.com/vedderb/bldc/blob/master/datatypes.h
//Updated on Sep 12, HmT
typedef enum {
    CAN_PACKET_SET_DUTY = 0,
    CAN_PACKET_SET_CURRENT,
    CAN_PACKET_SET_CURRENT_BRAKE,
    CAN_PACKET_SET_RPM,
    CAN_PACKET_SET_POS,
    CAN_PACKET_FILL_RX_BUFFER,
    CAN_PACKET_FILL_RX_BUFFER_LONG,
    CAN_PACKET_PROCESS_RX_BUFFER,
    CAN_PACKET_PROCESS_SHORT_BUFFER,
    CAN_PACKET_STATUS,
    CAN_PACKET_SET_CURRENT_REL,
    CAN_PACKET_SET_CURRENT_BRAKE_REL,
    CAN_PACKET_SET_CURRENT_HANDBRAKE,
    CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
    CAN_PACKET_STATUS_2,
    CAN_PACKET_STATUS_3,
    CAN_PACKET_STATUS_4,
    CAN_PACKET_PING,
    CAN_PACKET_PONG,
    CAN_PACKET_DETECT_APPLY_ALL_FOC,
    CAN_PACKET_DETECT_APPLY_ALL_FOC_RES,
    CAN_PACKET_CONF_CURRENT_LIMITS,
    CAN_PACKET_CONF_STORE_CURRENT_LIMITS,
    CAN_PACKET_CONF_CURRENT_LIMITS_IN,
    CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN,
    CAN_PACKET_CONF_FOC_ERPMS,
    CAN_PACKET_CONF_STORE_FOC_ERPMS,
    CAN_PACKET_STATUS_5,
    CAN_PACKET_POLL_TS5700N8501_STATUS,
    CAN_PACKET_CONF_BATTERY_CUT,
    CAN_PACKET_CONF_STORE_BATTERY_CUT,
    CAN_PACKET_SHUTDOWN
} CAN_PACKET_ID;

void vesc::vesc_init(int CAN_ID, CAN* _CAN)//pass the CAN address(pointer) into class
{
    controller_id = CAN_ID;
    CAN0 = _CAN;
    CAN0->frequency(1000000);
}

void vesc::buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) 
{
   buffer[(*index)++] = number >> 24;
   buffer[(*index)++] = number >> 16;
   buffer[(*index)++] = number >> 8;
   buffer[(*index)++] = number;
}

bool vesc::sendPacket(uint32_t id, uint8_t packet[], int32_t len)
{
   if (CAN0->write(CANMessage(id, (const char*)packet, sizeof(packet),CANData,CANExtended)))
   {   
      return true;
   }
   else {
      //CAN0->reset();
      //Serial.println("Error Sending Message...");
      return false;
   }
}
//Here I remove the input argument "controller_id"
//In order to make one vesc instantiate a single VESC
void vesc::comm_can_set_duty(float duty) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
    sendPacket(controller_id |
            ((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

void vesc::comm_can_set_current(float current) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
    sendPacket(controller_id |
            ((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

void vesc::comm_can_set_current_brake(float current) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
    sendPacket(controller_id |
            ((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), buffer, send_index);
}

void vesc::comm_can_set_rpm(float rpm) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)rpm, &send_index);
    sendPacket(controller_id |
            ((uint32_t)CAN_PACKET_SET_RPM << 8), buffer, send_index);
}

void vesc::comm_can_set_pos(float pos) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(pos * 1000000.0), &send_index);
    sendPacket(controller_id |
            ((uint32_t)CAN_PACKET_SET_POS << 8), buffer, send_index);
}
    
void vesc::stop(){
    comm_can_set_rpm(0);
}
