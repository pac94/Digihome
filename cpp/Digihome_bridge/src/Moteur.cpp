#include "../include/Moteur.h"

Moteur::Moteur(string _room, int _pinNumber):Equipement(_room, 2)
{
    pin.Setnumber(_pinNumber);
}

Moteur::~Moteur()
{
    //dtor
}

void Moteur::allumer()
{
    pin.Setstate(1);
}

void Moteur::eteindre()
{
    pin.Setstate(0);
}

void Moteur::ToArduinoFormat(int* buff)
{
    buff[0] = 0x7E;
    buff[1] = 0x03;
    buff[2] = 0x01;
    buff[3] = pin.Getnumber();
    buff[4] = pin.Getstate();
    buff[9] = 0xE7;
}
