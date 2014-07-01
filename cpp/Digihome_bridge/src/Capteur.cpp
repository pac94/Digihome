#include "../include/Capteur.h"
#include <jsoncpp/json.h>

Capteur::Capteur(string _room, string _type, float _value)
{
    room = _room;
    type = _type;
    value = _value;
}

Capteur::~Capteur()
{

}

Json::Value Capteur::ToJsonFormat()
{
    Json::Value capteur;
    capteur["room"] = room;
    capteur["sensor"] = type;
    capteur["value"] = value;

    return capteur;
}
