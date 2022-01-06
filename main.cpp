#include <eggxlib.h>
#include <stdio.h>
#include <iostream>
#include "weggx.hpp"
#include "form.hpp"
#include "test_scene.hpp"

using namespace std;

int main()
{
    TestForm* test_scene = new TestForm(new Weggx(WindowInfo{24,500,500}));
    delete test_scene;
    while(1);
}