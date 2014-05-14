#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <string>
using namespace std;

class Equipement
{
    public:
        Equipement(string _room, int _type);
        virtual ~Equipement();
        virtual void allumer() = 0;
        virtual void eteindre() = 0;
        virtual void ToArduinoFormat(int *buff) = 0;
        string Getroom(){ return room;};
        int Gettype(){return type;};
    protected:
    private:
        int type;
        string room;
};

#endif // EQUIPEMENT_H
