#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <string>
using namespace std;
#include <jsoncpp/json.h>

class Capteur
{
    public:
        Capteur(string _room, string _type, float _value);
        virtual ~Capteur();
        string Gettype() { return type; }
        void Settype(string val) { type = val; }
        string Getroom() { return room; }
        void Setroom(string val) { room = val; }
        float Getvalue() { return value; }
        void Setvalue(float val) { value = val; }
        Json::Value ToJsonFormat();
    protected:
    private:
        string type;
        string room;
        float value;
};

#endif // CAPTEUR_H
