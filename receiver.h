#include "mbed.h"
#include "DS4_BT_Serial_Host_Shield.h"


class receiver
{
    public: 
        receiver(BufferedSerial*);    
        
        void receiver_read();
       
        float rpm = 0;
        float pos_past = 0;
        float pos = 0;
        
        float rotationL = 0;
        float rotationR = 0;
        
        bool button1;
        bool button2;
        bool button3;
        bool button4;
        bool turnL;
        bool turnR;
        
        int mode;
        DS4_BT_Serial_Host_Shield *DS4_BT_1;
        float utils_fast_atan2(float y, float x);

        
        float M_PI = 3.14159265359;
        float x_dir;
        float y_dir;
        float sq;
    };

