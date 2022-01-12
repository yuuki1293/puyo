#ifndef GAME_FORM_HPP
#define GAME_FORM_HPP

#include "weggx.hpp"
#include "form.hpp"
#include "button.hpp"

class GameForm : public Form
{
private:
public:
    void initialize() override;
    void load() override;
    GameForm(Weggx *, int, int, int);
    ~GameForm();
};

void GameForm::initialize()
{
    this->ui.push_back(new Button(weggx, UIInfo{100, 500, 30, 30, 1, "#D0D0D0"}));
    this->ui[0]->click_event = [&](UI *ui, ClickEventArgs args)
    { ui->info.x += 10; };
    this->ui.push_back(new Button(weggx, UIInfo{100, 300, 20, 20, 2, "#f8ff00"}));
    this->ui[1]->click_event = [&](UI *ui, ClickEventArgs args)
    {ui->info.width+=10;ui->info.height+=10; };
}

void GameForm::load()
{
    // NOTE 遅延を挟まないとうまく動作しない
    while (1)
    {
        eggx_msleep(10);
    }
}

GameForm::GameForm(Weggx *weggx, int row, int column, int bomb_num) : Form()
{
    this->weggx = weggx;
    initialize();
    load_th = std::thread([&]
                          { load(); });
}

GameForm::~GameForm()
{
}

#endif // GAME_FORM_HPP