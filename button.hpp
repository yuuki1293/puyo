#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "weggx.hpp"
#include "user_interface.hpp"
#include <functional>

class Button : public UI
{
protected:
    std::function<void(UI *, ClickEventArgs)> button_click_event = [](UI *e, ClickEventArgs args) {};

public:
    bool enable;
    Button(Weggx *, UIInfo);
};

Button::Button(Weggx *weggx, UIInfo info) : UI(weggx, info)
{
    this->click_event = [&](UI *e, ClickEventArgs args)
    {
        if (enable)
            button_click_event(e, args);
    };
    this->drow = [&]
    {
        this->weggx->set_pen_color(this->info.color);
        double xs = this->info.x;
        double ys = this->info.y;
        double xe = xs + this->info.width;
        double ye = ys + this->info.height;
        this->weggx->drow_rect(xs, ys, xe, ye);
    };
    this->on_cursor = [&](UI *e, ClickEventArgs args)
    {
        return e->info.x < args.x 
            && e->info.x + e->info.width > args.x
            && e->info.y < args.y
            && e->info.y + e->info.height > args.y;
    };
}

#endif // BUTTON_HPP