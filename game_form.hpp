#ifndef GAME_FORM_HPP
#define GAME_FORM_HPP

#include "weggx.hpp"
#include "form.hpp"

class GameForm : public Form
{
private:
public:
    void initialize() override{
        
    }
    GameForm(Weggx*,int,int,int);
    ~GameForm();
};

GameForm::GameForm(Weggx* weggx,int row,int column,int bomb_num)
{
    this->weggx = weggx;
}

GameForm::~GameForm()
{
}


#endif//GAME_FORM_HPP