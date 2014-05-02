#ifndef COLOR_H
#define COLOR_H


class Color
{
    public:
        Color();
        virtual ~Color();
        int Get_state() { return state; }
        void Set_state(int val) { state = val; }
        int Get_pin() { return pin; }
        void Set_pin(int val) { pin = val; }
    protected:
    private:
         int pin;
         int state;
};

#endif // COLOR_H
