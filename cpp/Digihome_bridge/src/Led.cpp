#include "../include/Led.h"
#include "../include/Pin.h"

Led::Led(string _room, int _Red_pin, int _Green_pin, int _Blue_pin)
{
    room = _room;
    red.Setnumber( _Red_pin);
    green.Setnumber( _Green_pin);
    blue.Setnumber( _Blue_pin);
    type = 1;
}

Led::~Led()
{
    //dtor
}
void Led::Set_led_color(int red_state, int green_state, int blue_state)
{
    red.Setstate(red_state);
    green.Setstate(green_state);
    blue.Setstate(blue_state);
}

int Led::To_serial_format(int* buff)
{
    buff[0] = 0x7E;
    buff[1] = 0x07;
    buff[2] = 0x01;
    buff[3] = red.Getnumber();
    buff[4] = red.Getstate();
    buff[5] = green.Getnumber();
    buff[6] = green.Getstate();
    buff[7] = blue.Getnumber();
    buff[8] = blue.Getstate();
    buff[9] = 0xE7;
    return 10;
}

int Led::get_type()
{
    return type;
}
