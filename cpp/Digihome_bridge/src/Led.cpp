#include "../include/Led.h"
#include "../include/Color.h"

Led::Led(string _room, int _Red_pin, int _Green_pin, int _Blue_pin)
{
    room = _room;
    red.Set_pin( _Red_pin);
    green.Set_pin( _Green_pin);
    blue.Set_pin( _Blue_pin);
}

Led::~Led()
{
    //dtor
}
void Led::Set_led_color(int red_state, int green_state, int blue_state)
{
    red.Set_state(red_state);
    green.Set_state(green_state);
    blue.Set_state(blue_state);
}

int Led::To_serial_format(int* buff)
{
    buff[0] = 0x7E;
    buff[1] = 0x07;
    buff[2] = 0x01;
    buff[3] = red.Get_pin();
    buff[4] = red.Get_state();
    buff[5] = green.Get_pin();
    buff[6] = green.Get_state();
    buff[7] = blue.Get_pin();
    buff[8] = blue.Get_state();
    buff[9] = 0xE7;
    return 10;
}
