#ifndef CHAUFFAGE_H
#define CHAUFFAGE_H
#include <string>
#include "Pin.h"
#include "Equipement.h"
#include <jsoncpp/json.h>
using namespace std;

class Chauffage : public Equipement
{
    public:
        Chauffage(string _room, int _pin);
        virtual ~Chauffage();
        void allumer();
        void eteindre();
        uint8_t ToArduinoFormat(uint8_t* buff);
        Json::Value ToJsonFormat();
    protected:
    private:
        Pin pin;
        string room;
};

#endif // CHAUFFAGE_H
