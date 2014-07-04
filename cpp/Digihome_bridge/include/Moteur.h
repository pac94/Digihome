#ifndef MOTEUR_H
#define MOTEUR_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
#include <jsoncpp/json.h>
using namespace std;

class Moteur : public Equipement
{
    public:
        Moteur(string _room, int _pinDir, int _pinBrake);
        virtual ~Moteur();
        void allumer();
        void eteindre();
        void set_motor_value(int val);
        void set_pin_state(int pinDirVal, int pinBrakeVal);
        int get_motor_value();
        uint8_t ToArduinoFormat(uint8_t* buff);
        Json::Value ToJsonFormat();
    protected:
    private:
        Pin pinDir;
        Pin pinBrake;
        string room;
};

#endif // MOTEUR_H
