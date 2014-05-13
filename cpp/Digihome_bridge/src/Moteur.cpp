#include "../include/Moteur.h"

Moteur::Moteur(string _room, int _pinNumber)
{
    pin.Setnumber(_pinNumber);
    room = _room;
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
