#ifndef LED_H
#define LED_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
using namespace std;

class Led : public Equipement
{
    public:
        Led(string room, int Red_pin, int Green_pin, int Blue_pin);
        virtual ~Led();
        void allumer();
        void eteindre();
        void Set_led_color(int red_state, int green_state, int blue_state);
        int Get_led_color();
        uint8_t ToArduinoFormat(uint8_t* buff);
    protected:
    private:
        Pin red;
        Pin blue;
        Pin green;
        int type;
};

#endif // LED_H
