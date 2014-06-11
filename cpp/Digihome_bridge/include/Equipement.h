#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <string>
#include <inttypes.h>
using namespace std;

class Equipement
{
    public:
        Equipement(string _room, string _type);
        virtual ~Equipement();
        virtual void allumer() = 0;
        virtual void eteindre() = 0;
        virtual uint8_t ToArduinoFormat(uint8_t *buff) = 0;
        //virtual void Set_led_color(int red_state, int green_state, int blue_state) {};
        string Getroom(){ return room;};
        string Gettype(){return type;};
    protected:
    private:
        string type;
        string room;
};

#endif // EQUIPEMENT_H
