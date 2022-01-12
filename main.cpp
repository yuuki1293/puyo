#include <eggxlib.h>
#include <stdio.h>
#include <iostream>
#include "weggx.hpp"
#include "form.hpp"
#include "test_scene.hpp"
#include "minesweeper_core.hpp"
#include "game_form.hpp"
#include "start.hpp"

int main()
{
    eggx_gsetinitialattributes(BOTTOM_LEFT_ORIGIN, DISABLE);
    eggx_gsetinitialattributes(SCROLLBAR_INTERFACE, ENABLE);
    eggx_gsetinitialattributes(MAX_WINDOW_SIZE, DISABLE);
    eggx_gsetinitialattributes(OVERRIDE_REDIRECT, DISABLE);
    eggx_gsetinitialattributes(DOCK_APPLICATION, DISABLE);
    auto weggx = new Weggx(WindowInfo{24, 500, 500}, "mine sweeper");
    Start::start(weggx);
    //form = new GameForm(weggx, 20, 20, 60);
    while (true); //NOTE 正常終了するとバグが発生するのでCtrl+Cもしくは例外を発生させる
}