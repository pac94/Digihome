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
        Chauffage(const Chauffage& other);
        void allumer();
        void eteindre();
        Chauffage& operator=(const Chauffage& other);
    protected:
    private:
        Pin pin;
        string room;
};

#endif // CHAUFFAGE_H
