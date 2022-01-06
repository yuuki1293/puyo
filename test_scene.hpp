#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP

#include "form.hpp"

class TestForm : public Form
{
public:
    void initialize() override
    {
        gsetinitialattributes(DISABLE, BOTTOM_LEFT_ORIGIN);
    }
    Weggx* get_weggx(){
        return this->weggx;
    }
    void load() override
    {
        weggx->move_pen(250, 250);
        weggx->drow_circle(50, 50);
        weggx->show();
    }
    TestForm(Weggx *weggx)
    {
        initialize();
        this->weggx = weggx;
        load();
    }
};

#endif