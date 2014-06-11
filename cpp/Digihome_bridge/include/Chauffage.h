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
        uint8_t ToArduinoFormat(uint8_t* buff);
    protected:
    private:
        Pin pin;
};

#endif // CHAUFFAGE_H
