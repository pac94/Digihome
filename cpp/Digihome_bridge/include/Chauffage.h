#ifndef CHAUFFAGE_H
#define CHAUFFAGE_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
using namespace std;

class Chauffage : public Equipement
{
    public:
        Chauffage(string _room, int _pin);
        virtual ~Chauffage();
        void allumer();
        void eteindre();
    protected:
    private:
        Pin pin;
};

#endif // CHAUFFAGE_H
