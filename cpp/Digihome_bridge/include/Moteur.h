#ifndef MOTEUR_H
#define MOTEUR_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
using namespace std;

class Moteur
{
    public:
        Moteur(string _room, int _pinNumber);
        virtual ~Moteur();
        void allumer();
        void eteindre();
    protected:
    private:
    Pin pin;
    string room;
};

#endif // MOTEUR_H
