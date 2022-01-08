#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include "weggx.hpp"
#include <functional>
#include "event.hpp"
#include <future>

class UI
{
private:
    Weggx *weggx;
    double height;
    double width;
    double depth;
    std::function<void(UI *, ClickEventArgs)> click_event = [](UI *e, ClickEventArgs args) {};
    std::function<void(UI *, PressKeyEventArgs)> press_key_event = [](UI *e, PressKeyEventArgs args) {};
    void initialize();

public:
    UI() {initialize();}
    ~UI() { delete weggx; }
};

void UI::initialize()
{
    auto th = std::thread([this] {
        int wn,type,button;
        double x,y;
        while (true)
        {
            if(eggx_ggetxpress(&type,&button,&x,&y) == this->weggx->get_window_number()){
                switch (type)
                {
                case ButtonPress:
                    this->click_event(this,ClickEventArgs{x,y,button});
                    break;
                case KeyPress:
                    this->press_key_event(this,PressKeyEventArgs{x,y,button});
                }
            }
        }
    });
    th.join();
}

#endif // USER_INTERFACE_HPP