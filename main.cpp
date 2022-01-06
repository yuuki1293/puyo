#include <eggxlib.h>
#include <stdio.h>
#include <iostream>
#include "weggx.hpp"
#include "form.hpp"
#include "test_scene.hpp"

using namespace std;

int main()
{
    //TestForm* test_scene = new TestForm(new Weggx(WindowInfo{24,500,500}));
    eggx_gcloseall();
    int w = eggx_gopen(500,500);
    for(int i = 0;i<100;i++){
        int k = eggx_ggetch();
        printf("%d\n",k);
    }
    //eggx_gclose(w);
    eggx_gcloseall();
    //delete test_scene;
}