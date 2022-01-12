#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include "weggx.hpp"
#include <functional>
#include "event.hpp"
#include <future>

struct UIInfo
{
    double x;
    double y;
    double width;
    double height;
    int depth;
    const char *color;
};

class UI
{
protected:
    Weggx *weggx;

public:
    UI(Weggx *, UIInfo);
    ~UI();
    bool operator<(const UI *r)
    {
        return this->info.depth < r->info.depth;
    }
    bool operator>(const UI *r)
    {
        return this->info.depth > r->info.depth;
    }
    std::function<void(UI *, ClickEventArgs)> click_event = [](UI *e, ClickEventArgs args) {};
    std::function<void(UI *, PressKeyEventArgs)> press_key_event = [](UI *e, PressKeyEventArgs args) {};
    std::function<void()> drow = [] {};
    std::function<bool(UI *, ClickEventArgs)> on_cursor = [](UI *e, ClickEventArgs args)
    { return false; };
    UIInfo info;
    bool visible = true;
};

UI::UI(Weggx *weggx, UIInfo info)
{
    this->weggx = weggx;
    this->info = info;
}

UI::~UI()
{
}

#endif // USER_INTERFACE_HPP