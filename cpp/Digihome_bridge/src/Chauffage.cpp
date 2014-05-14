#include "../include/Chauffage.h"

Chauffage::Chauffage(string _room, int _pin):Equipement(_room, 3)
{
    pin.Setnumber(_pin);
}

Chauffage::~Chauffage()
{
    //dtor
}

void Chauffage::allumer()
{
    pin.Setstate(1);
}

void Chauffage::eteindre()
{
    pin.Setstate(0);
}

void Chauffage::ToArduinoFormat(int* buff)
{
    buff[0] = 0x7E;
    buff[1] = 0x03;
    buff[2] = 0x01;
    buff[3] = pin.Getnumber();
    buff[4] = pin.Getstate();
    buff[9] = 0xE7;
}
