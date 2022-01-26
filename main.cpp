/* config */
int column = 7;
int row = 10;
int bombs = 11;

const char *color_text = "#FFFFFF";
const char *color_behind = "#000000";
const char *color_unknown = "#E0E0E0";
const char *color_flag = "#F8FF00";
const char *color_bomb = "#595963";
const char *color_num[] = {"#595963", "#19BDDF", "#779A22", "#DC2069", "#1A55C2", "#B72222", "#1C8E38", "#8A2C8A", "#E05B19"};
/* config */

#include <stdio.h>
#include "weggx.hpp"
#include "minesweeper_core.hpp"

const int unknown = -1;
const int flag = -2;
const int bomb = -3;

int to_column(double x) { return (x - 10) / 32; }
int to_row(double y) { return (y - 200) / 32; }
int around[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

std::vector<std::vector<int>> cell;

Weggx *weggx;
MSCore *mscore;

void draw_cell(int type, int column, int row)
{
    switch (type)
    {
    case unknown:
        weggx->set_pen_color(color_unknown);
        weggx->draw_rect(column * 32 + 10, row * 32 + 200, 31, 31);
        break;
    case flag:{
        weggx->set_pen_color(color_flag);
        weggx->draw_rect(column * 32 + 10, row * 32 + 200, 31, 31, false);
        double x[3]={(double)(column * 32 + 20), (double)(column * 32 + 31), (double)(column * 32 + 20)};
        double y[3]={(double)(row * 32 + 205), (double)(row * 32 + 212), (double)(row * 32 + 219)};
        weggx->draw_poly(x, y, 3);
        weggx->move_pen(column * 32 + 21,row * 32 + 219);
        weggx->pen_down();
        weggx->move_pen(column * 32 + 21,row * 32 + 230);
        weggx->pen_up();
        weggx->set_pen_color(color_text);
        weggx->move_pen(30, 100);
        weggx->draw_text(20, ("bombs:" + std::to_string(mscore->get_rest_bomb())).c_str());
        break;}
    case bomb:{
        weggx->set_pen_color(color_bomb);
        weggx->draw_rect(column * 32 + 10, row * 32 + 200, 31, 31);
        weggx->set_pen_color(color_behind);
        weggx->move_pen(column * 32 + 26, row * 32 + 216);
        weggx->set_pen_width(3);
        weggx->draw_symbol(24, 3);
        weggx->set_pen_width(2);
        break;}
    default:
        weggx->set_pen_color(color_num[type]);
        weggx->draw_rect(column * 32 + 10, row * 32 + 200, 31, 31, false);
        weggx->move_pen(column * 32 + 14, row * 32 + 216);
        weggx->draw_text(20, std::to_string(type).c_str());
        break;
    }
}

void draw_cells()
{
    weggx->grafic_clear();
    for (int i = 0; i < row; i++)
    for (int j = 0; j < column; j++)
    draw_cell(cell[i][j], j, i);
}

void open_around(int rowo, int columno)
{
    int row, column;
    for(int i = 0; i < 8; i++)
    {
        row = rowo + around[i][0];
        column = columno + around[i][1];
        int result = mscore->left_click(posi{row, column});
        if (result <= -2);
        else if(result == -1) cell[row][column] = bomb;
        else if(result == 0) { open_around(row, column); cell[row][column] = result; }
        else cell[row][column] = result;
    }
}

void setup()
{
    cell.resize(row);
    for (int i = 0; i < row; i++)
        cell[i].resize(column);
    for (int i = 0; i < row; i++)
    for (int j = 0; j < column; j++)
        cell[i][j] = -1;
    
    weggx->set_window_size(column * 32 + 20, row * 32 + 200);
    weggx->set_pen_width(2);
    draw_cells();
    weggx->show();
}

void start()
{
    double x, y;
    int type, button;
    while (!mscore->get_status())
    {
        weggx->get_key_click(&type, &button, &x, &y); // NOTE 左:1 中:2 右:3
        int row = to_row((int)y);
        int column = to_column((int)x);
        if (type == ButtonPress)
        {
            int result;
            switch (button)
            {
            case 1: //左
                result = mscore->left_click(posi{row, column});
                if (result <= -2);
                else if(result == -1) cell[row][column] = bomb;
                else if(result == 0) { open_around(row, column); cell[row][column] = result; }
                else cell[row][column] = result;
                break;
            case 2: //中
                if (cell[row][column] >= 0 && cell[row][column] == mscore->get_around_flags(posi{row, column}))
                    open_around(row, column);
                break;
            case 3: //右
                result = mscore->right_click(posi{row, column});
                if (result <= -1);
                else if(result == 0) cell[row][column] = flag;
                else if(result == 1) cell[row][column] = unknown;
                break;
            default:
                break;
            }
            draw_cells();
            weggx->show();
        }
    }
    if(mscore->get_status() == 1) 
    {
        for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
        if(mscore->left_click(posi{i, j}) == -1)
            cell[i][j] = bomb;
        draw_cells();
        weggx->show();
        printf("ゲームオーバーだよ!\n");
    }
    else if(mscore->get_status() == 2) 
        printf("クリアだよ!\n");
    else
        printf("unexpected result\n");
}

int main(int argc, char *argv[])
{
    eggx_gsetinitialattributes(DISABLE, BOTTOM_LEFT_ORIGIN);
    eggx_gsetinitialattributes(ENABLE, SCROLLBAR_INTERFACE);
    eggx_gsetinitialattributes(DISABLE, MAX_WINDOW_SIZE);
    eggx_gsetinitialattributes(DISABLE, OVERRIDE_REDIRECT);
    eggx_gsetinitialattributes(DISABLE, DOCK_APPLICATION);
    if(argc >= 3)
    {
        row = atoi(argv[1]);
        column = atoi(argv[2]);
        bombs = atoi(argv[3]);
    }
    weggx = new Weggx("mine sweeper");
    mscore = new MSCore(row, column, bombs);
    setup();
    start();
    while (true)
        ; // NOTE 正常終了するとバグが発生する
}