#include "../include/Chauffage.h"

Chauffage::Chauffage(string _room, int _pin):Equipement(_room, "ac")
{
    room = _room;
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

uint8_t Chauffage::ToArduinoFormat(uint8_t* buff)
{
    buff[0] = 0x7E;
    buff[1] = 0x03;
    buff[2] = 0x01;
    buff[3] = pin.Getnumber();
    buff[4] = pin.Getstate();
    buff[5] = 0xE7;
    return 6;
}

Json::Value Chauffage::ToJsonFormat()
{
    Json::Value led;
    led["sensor"] = "ac";

        led["value"] = pin.Getstate();

    led["location"] = room;

    return led;
}
