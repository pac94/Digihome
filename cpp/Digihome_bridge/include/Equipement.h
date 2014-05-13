#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <string>

class Equipement
{
    public:
        Equipement(string _room, int _type);
        virtual ~Equipement();
        virtual int get_type() = 0;
        virtual void allumer() = 0;
        virtual void eteindre() = 0;
    protected:
    private:
        int type;
        string room;
};

#endif // EQUIPEMENT_H
