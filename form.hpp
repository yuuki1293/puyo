#ifndef SCENE_MANEGE_HPP
#define SCENE_MANEGE_HPP

#include "weggx.hpp"
#include <vector>
#include <functional>
#include <algorithm>
#include "user_interface.hpp"

class Form
{
private:
    void sort_ui();
    std::thread drow_th;
    std::thread listner_th;
    bool th_flag = true;

protected:
    Weggx *weggx;
    std::vector<UI *> ui;
    std::thread load_th;

public:
    virtual void initialize() = 0;
    virtual void load() = 0;
    Form();
    virtual ~Form();
};

void Form::sort_ui()
{
    std::stable_sort(ui.begin(), ui.end());
}

Form::Form()
{
    drow_th = std::thread([&]()
                          {
            while(th_flag){
                weggx->grafic_clear();
                for(const auto& e:ui)
                    {
                        if(e->visible)
                            e->drow();
                    }
                weggx->show();
                eggx_msleep(100);
            } });
    printf("1\n");
    listner_th = 
        std::thread([&]()
                    {
                        double x,y;
                        int button,type;
                        while (th_flag)
                        {
                            printf("listner_th1\n");
                            weggx->get_key_click(&type,&button,&x,&y);
                            switch (type)
                            {
                            case ButtonPress:
                                std::for_each(ui.rbegin(),ui.rend(),[&](UI* ui){if(ui->visible&&ui->on_cursor(ui,ClickEventArgs{x,y,button}))ui->click_event(ui,ClickEventArgs{x,y,button});});
                                break;
                            case KeyPress:
                                break;
                            }
                    }
                    });
    printf("2\n");
}

Form::~Form()
{
    th_flag = false;
    eggx_msleep(30);
}

#endif // SCENE_MANEGE_HPP