#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H


class Equipement
{
    public:
        Equipement();
        virtual ~Equipement();
        virtual int get_type() = 0;
    protected:
    private:
        int type;
        int room;
};

#endif // EQUIPEMENT_H
