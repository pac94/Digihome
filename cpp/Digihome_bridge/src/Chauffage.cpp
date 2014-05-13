#include "../include/Chauffage.h"

Chauffage::Chauffage(string _room, int _pin)
{
    pin.Setnumber(_pin);
    room = _room;
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

Chauffage::Chauffage(const Chauffage& other)
{
    //copy ctor
}

Chauffage& Chauffage::operator=(const Chauffage& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
