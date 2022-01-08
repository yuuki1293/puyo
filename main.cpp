#include <eggxlib.h>
#include <stdio.h>
#include <iostream>
#include "weggx.hpp"
#include "form.hpp"
#include "test_scene.hpp"
#include "minesweeper_core.hpp"

using namespace std;

int main()
{
    eggx_gsetinitialattributes(BOTTOM_LEFT_ORIGIN, DISABLE);
    eggx_gsetinitialattributes(SCROLLBAR_INTERFACE, ENABLE);
    eggx_gsetinitialattributes(MAX_WINDOW_SIZE, DISABLE);
    eggx_gsetinitialattributes(OVERRIDE_REDIRECT, DISABLE);
    eggx_gsetinitialattributes(DOCK_APPLICATION, DISABLE);

    while(true);
}