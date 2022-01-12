/* config */
#define COLUMN 50
#define ROW 40
#define BOMBS 50

#define UNKNOWN_COLOR "#E0E0E0"
#define FLAG_COLOR "#F8FF00"
/* config */

#include <stdio.h>
#include "weggx.hpp"
#include "minesweeper_core.hpp"

#define UNKNOWN -1
#define FLAG -2
#define BOMB -3

#define TOCOLUMN(x) (x - 10) / 32
#define TOROW(y) (y - 200) / 32

int cell[ROW][COLUMN];

Weggx weggx("mine sweeper");
MSCore mscore(ROW, COLUMN, BOMBS);

void draw_cell(int type, int column, int row)
{
    switch (type)
    {
    case UNKNOWN:
        weggx.set_pen_color(UNKNOWN_COLOR);
        weggx.draw_rect(column * 32 + 10, row * 32 + 200, 31, 31);
        break;
    case FLAG:{
        weggx.set_pen_color(FLAG_COLOR);
        weggx.draw_rect(column * 32 + 10, row * 32 + 200, 31, 31, false);
        double x[3]={(double)(column * 32 + 20), (double)(column * 32 + 31), (double)(column * 32 + 20)};
        double y[3]={(double)(row * 32 + 205), (double)(row * 32 + 212), (double)(row * 32 + 219)};
        weggx.draw_poly(x, y, 3);
        weggx.move_pen(column * 32 + 20,row * 32 + 219);
        weggx.pen_down();
        weggx.move_pen(column * 32 + 20,row * 32 + 230);
        weggx.pen_up();
        break;}
    case BOMB:
        // TODO 爆弾を描画
        break;
    default:
        // TODO 開けられたセルを描画
        break;
    }
}

void draw_cells()
{
    weggx.grafic_clear();
    for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COLUMN; j++)
    draw_cell(cell[i][j], j, i);
}

void setup()
{
    for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COLUMN; j++)
    cell[i][j] = -1;
    
    weggx.set_window_size(COLUMN * 32 + 20, ROW * 32 + 200);
    draw_cells();
    weggx.show();
}

void start()
{
    double x, y;
    int type, button;
    while (!mscore.get_status())
    {
        weggx.get_key_click(&type, &button, &x, &y); // NOTE 左:1 中:2 右:3
        int row = TOROW((int)y);
        int column = TOCOLUMN((int)x);
        if (type == ButtonPress)
        {
            int result;
            switch (button)
            {
            case 1: //左
                result = mscore.left_click(posi{row, column});
                if (result <= -2);
                else if(result == -1) cell[row][column] = BOMB;
                else cell[row][column] = result;
                break;
            case 2: //中
                break;
            case 3: //右
                result = mscore.right_click(posi{row, column});
                if (result <= -1);
                else if(result == 0) cell[row][column] = FLAG;
                else if(result == 1) cell[row][column] = UNKNOWN;
                break;
            default:
                break;
            }
            draw_cells();
            weggx.show();
        }
    }
    if(mscore.get_status()==1)printf("ゲームオーバーだよ!\n");
    else printf("クリアだよ!\n");
}

int main()
{
    eggx_gsetinitialattributes(DISABLE, BOTTOM_LEFT_ORIGIN);
    eggx_gsetinitialattributes(ENABLE, SCROLLBAR_INTERFACE);
    eggx_gsetinitialattributes(DISABLE, MAX_WINDOW_SIZE);
    eggx_gsetinitialattributes(DISABLE, OVERRIDE_REDIRECT);
    eggx_gsetinitialattributes(DISABLE, DOCK_APPLICATION);
    setup();
    start();
    while (true)
        ; // NOTE 正常終了するとバグが発生するのでCtrl+Cもしくは例外を発生させる
}