#ifndef DS4_BT_SERIAL_HOST_SHIELD_H
#define DS4_BT_SERIAL_HOST_SHIELD_H

#include "mbed.h"
#include <cstdio>
//#define  DS4_BT_Debug

class DS4_BT_Serial_Host_Shield {
public:
  DS4_BT_Serial_Host_Shield(BufferedSerial *_DS4_BT_BufferedSerial);
  void getPacket();
  void parsePacket();
  uint8_t getc();
  void sendr();
  struct DS4_Input_Struct {
    bool Triangle = 0;
    bool Circle = 0;
    bool Cross = 0;
    bool Square = 0;
    bool DPAD_N = 0;
    bool DPAD_NW = 0;
    bool DPAD_W = 0;
    bool DPAD_SW = 0;
    bool DPAD_S = 0;
    bool DPAD_SE = 0;
    bool DPAD_E = 0;
    bool DPAD_NE = 0;
    bool Options = 0;
    bool Share = 0;
    bool R2 = 0;
    bool L2 = 0;
    bool R1 = 0;
    bool L1 = 0;
    bool Touchpad = 0;
    bool Touchpad_Finger_0 = 0;
    bool Touchpad_Finger_1 = 0;
    bool PS = 0;

    bool R3 = 0;
    bool L3 = 0;
    int Lstick_x = 0;
    int Lstick_y = 0;
    int Rstick_x = 0;
    int Rstick_y = 0;
    int L2_Trigger = 0;
    int R2_Trigger = 0;

  } DS4_Input;
  
private:
  uint8_t DS4_BT_Packet[18] = {0};
  uint8_t buf[1]= {0};
  char r[1] = {'R'};
  BufferedSerial *DS4_BT_BufferedSerial;

  // BufferedSerial device(PA_9, PA_10);
  /*
    enum DS4_Buttons_Bit : uint8_t {

      Triangle = 0x01,
      Circle = 0x02,
      Cross =0x04,
      Square = 0x08,
      DPAD_N =0x10,
      DPAD_E =0x20,
      DPAD_S =0x40,
      DPAD_W =0x80,
      L1 = 0x01,
      L3 = 0x02,
      R1 =0x04,
      R3 =0x08,
      Share= 0x10,
      Options =0x20,
      Touchpad =0x40,
      PS=0x80,



      Touchpad_Finger_0=0x01,
      Touchpad_Finger_1=0x02,




    };
  */
};

#endif

