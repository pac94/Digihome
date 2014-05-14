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

