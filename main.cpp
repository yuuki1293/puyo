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
    int row,col,bomb;
    printf("縦 横 爆弾の数の順に入力してね\n");
    scanf("%d%d%d",&row,&col,&bomb);
    MSCore new_ms(row,col,bomb);
    while(1){
        printf("縦 横の順に入力してね\n");
        scanf("%d%d",&row,&col);
        int result = new_ms.click(posi{row,col});
        switch (result)
        {
        case -4:
            printf("範囲外だよ!\n");
            break;
        case -3:
            printf("もう開いてるよ!\n");
            break;
        case -2:
            printf("旗が立ってるよ!\n");
            break;
        case -1:
            printf("爆発したよ!\n");
            break;
        default:
            printf("(%d, %d) の数字は %d だよ!\n",row,col,result);
            break;
        }
        switch (new_ms.get_status())
        {
        case 1:
            printf("ゲームオーバー\n");
            std::exit(0);
            break;
        case 2:
            printf("ゲームクリア\n");
            std::exit(0);
        default:
            break;
        }
    }
}