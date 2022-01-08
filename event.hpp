#ifndef EVENT_HPP
#define EVENT_HPP

struct ClickEventArgs
{
    double x;
    double y;
    int button;
};

struct PressKeyEventArgs
{
    public:
    double x;
    double y;
    int key_cord;
};

#endif//EVENT_HPP