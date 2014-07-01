#ifndef LED_H
#define LED_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
#include <jsoncpp/json.h>
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
        Json::Value ToJsonFormat();
    protected:
    private:
        Pin red;
        Pin blue;
        Pin green;
        int type;
        string room;
};

#endif // LED_H
