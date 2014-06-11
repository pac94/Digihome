#ifndef MOTEUR_H
#define MOTEUR_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
using namespace std;

class Moteur : public Equipement
{
    public:
        Moteur(string _room, int _pinNumber);
        virtual ~Moteur();
        void allumer();
        void eteindre();
        uint8_t ToArduinoFormat(uint8_t* buff);
    protected:
    private:
        Pin pin;
};

#endif // MOTEUR_H
