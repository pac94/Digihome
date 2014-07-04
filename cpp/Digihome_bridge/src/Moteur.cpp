#include "../include/Moteur.h"

Moteur::Moteur(string _room, int _pinDir, int _pinBrake):Equipement(_room, "motor")
{
    room = _room;
    pinDir.Setnumber(_pinDir);
    pinBrake.Setnumber(_pinBrake);
}


Moteur::~Moteur()
{
    //dtor
}

void Moteur::set_motor_value(int val)
{
    switch(val)
    {
        case 0 :
                pinDir.Setstate(0);
                pinBrake.Setstate(1);
                break;

         case 1 :
                pinDir.Setstate(0);
                pinBrake.Setstate(0);
                break;

        case 2 :
                pinDir.Setstate(1);
                pinBrake.Setstate(0);
                break;

        default :
                pinDir.Setstate(0);
                pinBrake.Setstate(1);
                break;

    }

}

void Moteur::set_pin_state(int pinDirVal, int pinBrakeVal)
{
    pinDir.Setstate(pinDirVal);
    pinBrake.Setstate(pinBrakeVal);
}

int Moteur::get_motor_value()
{
    int val;


    if(pinDir.Getstate() == 0 && pinBrake.Getstate() == 1)
            val = 0;
    if(pinDir.Getstate() == 0 && pinBrake.Getstate() == 0)
    val = 1;
    if(pinDir.Getstate() == 1 && pinBrake.Getstate() == 0)
        val = 2;
    return val;
}

void Moteur::allumer()
{
    set_motor_value(0);
}

void Moteur::eteindre()
{
     set_motor_value(0);
}


uint8_t Moteur::ToArduinoFormat(uint8_t* buff)
{
    buff[0] = 0x7E;
    buff[1] = 0x05;
    buff[2] = 0x01;
    buff[3] = pinDir.Getnumber();
    buff[4] = pinDir.Getstate();
    buff[5] = pinBrake.Getnumber();
    buff[6] = pinBrake.Getstate();
    buff[7] = 0xE7;
    return 8;
}


Json::Value Moteur::ToJsonFormat()
{
    Json::Value led;
    led["sensor"] = "motor";
    int val = get_motor_value();

        led["value"] = val;

    led["location"] = room;

    return led;
}
