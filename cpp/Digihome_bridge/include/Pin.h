#ifndef PIN_H
#define PIN_H


class Pin
{
    public:
        Pin();
        virtual ~Pin();
        unsigned int Getnumber() { return number; }
        void Setnumber(unsigned int val) { number = val; }
        unsigned int Getstate() { return state; }
        void Setstate(unsigned int val) { state = val; }
    protected:
    private:
        unsigned int number;
        unsigned int state;
};

#endif // PIN_H
