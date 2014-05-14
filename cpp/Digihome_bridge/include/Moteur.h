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
        void ToArduinoFormat(int* buff);
    protected:
    private:
        Pin pin;
};

#endif // MOTEUR_H
