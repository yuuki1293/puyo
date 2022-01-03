#ifndef WEGGX_HPP
#define WEGGX_HPP

#include <eggx.h>

struct WindowInfo
{
    int depth;
    int width;
    int height;
};

class Weggx
{
private:
    int win_num;
    char *backgound_color;
    int pen_mode;
    int penx;
    int peny;

public:
    WindowInfo win_info;

    int get_window_number()
    {
        return this->win_num;
    }

    static void close_all()
    {
        gcloseall();
    }

    void set_background_color(const char *args)
    {
        *(this->backgound_color) = *args;
        gsetbgcolor(this->win_num, args);
    }

    void set_win_name(const char *win_title)
    {
        winname(this->win_num, win_title);
    }

    void set_border(int width, const char *args)
    {
        gsetborder(this->win_num, width, args);
    }

    void chnge_window_scale(float xs, float ys, float xe, float ye)
    {
        window(this->win_num, xs, ys, xe, ye);
    }

    void show()
    {
        copylayer(this->win_num, 1, 0);
    }

    /// 0: black    4: blue     8: dim gray     12: dark blue
    /// 1: white    5: cyan     9: gray         13: dark cyan
    /// 2: red      6: magenta  10: dark red    14: dark magenta
    /// 3: green    7: yellow   11: dark green  15: dark yellow
    void set_pen_color(int cn)
    {
        newpen(this->win_num, cn);
    }

    void set_pen_color(const char *args)
    {
        newcolor(this->win_num, args);
    }

    void set_pen_color(int r, int g, int b)
    {
        newrgbcolor(this->win_num, r, g, b);
    }

    static void console_clear()
    {
        tclr();
    }

    void grafic_clear()
    {
        gclr(this->win_num);
    }

    void drow_point(float x, float y)
    {
        pset(this->win_num, x, y);
    }

    void pen_up()
    {
        this->pen_mode = PENUP;
    }

    void pen_down()
    {
        this->pen_mode = PENDOWN;
    }

    void move_pen(float x, float y)
    {
        this->penx = x;
        this->peny = y;
        line(this->win_num, x, y, pen_mode);
    }

    void drow_circle(float xrad, float yrad, bool fill = true, float sang = 0, float eang = 360, int idir = 1)
    {
        if (fill)
            fillarc(this->win_num, this->penx, this->peny, xrad, yrad, sang, eang, idir);
        else
            drawarc(this->win_num, this->penx, this->peny, xrad, yrad, sang, eang, idir);
    }

    void drow_rect(float x1, float y1, float x2, float y2, bool fill = true)
    {
        if (fill)
            fillrect(this->win_num, x1, y1, (x2 - x1), (y2 - y1));
        else
            drawrect(this->win_num, x1, y1, (x2 - x1), (y2 - y1));
    }

    void drow_poly(float x[], float y[], int n, int i = 0)
    {
        fillpoly(this->win_num, x, y, n, i);
    }

    void draw_arrow(float xs, float ys, float xt, float yt, float s, float w, int i, int j)
    {
        drawarrow(this->win_num, xs, ys, xt, yt, s, w, i * 10 + j);
    }

    void drow_text(float x, float y, int size, const char *args)
    {
        drawstr(this->win_num, x, y, size, 0.0, args);
    }

    void set_font(const char* font){
        gsetfontset(this->win_num,font);
    }

    static int get_key(){
        return ggetch();
    }

    

    Weggx(const char *win_title = "space")
    {
        int depth, width, height;
        ggetdisplayinfo(&depth, &width, &height);
        this->win_info = WindowInfo{depth, width, height};
        this->win_num = gopen(win_info.width, win_info.height);
        winname(this->win_num, win_title);
        layer(this->win_num, 0, 1);
    }

    ~Weggx()
    {
        gclose(win_num);
    }
};

#endif // WEGGX_HPP