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
        string Get_room() { return room; }
        void Set_room(string val) { room = val; }
        void Set_led_color(int red_state, int green_state, int blue_state);
        int To_serial_format(int* buff);
        int get_type();
    protected:
    private:
        string room;
        Pin red;
        Pin blue;
        Pin green;
        int type;
};

#endif // LED_H
