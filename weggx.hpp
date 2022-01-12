#ifndef WEGGX_HPP
#define WEGGX_HPP

#define DEFAULT_WINDOW_NAME "new window"

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
    // PENDOWN = 2, PENUP = 3
    int pen_mode = PENUP;
    int penx = 0;
    int peny = 0;

public:
    WindowInfo win_info;

    int get_window_number()
    {
        return this->win_num;
    }

    void set_window_size(int width, int height)
    {
        eggx_gresize(this->win_num, width, height);
        win_info.width = width;
        win_info.height = height;
    }

    static void close_all()
    {
        eggx_gcloseall();
    }

    void resize(int xsize, int ysize)
    {
        eggx_gresize(this->win_num, xsize, ysize);
    }

    void set_win_name(const char *win_title)
    {
        eggx_winname(this->win_num, win_title);
    }

    void set_background_color(const char *args)
    {
        *(this->backgound_color) = *args;
        eggx_gsetbgcolor(this->win_num, args);
    }

    void set_border(int width, const char *args)
    {
        eggx_gsetborder(this->win_num, width, args);
    }

    void chnge_window_scale(double xs, double ys, double xe, double ye)
    {
        eggx_window(this->win_num, xs, ys, xe, ye);
    }

    void show()
    {
        eggx_copylayer(this->win_num, 1, 0);
    }

    /// 0: black    4: blue     8: dim gray     12: dark blue
    /// 1: white    5: cyan     9: gray         13: dark cyan
    /// 2: red      6: magenta  10: dark red    14: dark magenta
    /// 3: green    7: yellow   11: dark green  15: dark yellow
    void set_pen_color(int cn)
    {
        eggx_newpen(this->win_num, cn);
    }

    void set_pen_color(const char *args)
    {
        eggx_newcolor(this->win_num, args);
    }

    void set_pen_color(int r, int g, int b)
    {
        eggx_newrgbcolor(this->win_num, r, g, b);
    }

    static void console_clear()
    {
        eggx_tclr();
    }

    void grafic_clear()
    {
        eggx_gclr(this->win_num);
    }

    void draw_point(double x, double y)
    {
        eggx_pset(this->win_num, x, y);
    }

    void pen_up()
    {
        this->pen_mode = PENUP;
    }

    void pen_down()
    {
        this->pen_mode = PENDOWN;
    }

    /// Default = 1
    void set_pen_width(int width)
    {
        eggx_newlinewidth(this->win_num, width);
    }

    /// LineSolid (default) = 0, LineOnOffDash = 1, LineDoubleDash = 2
    void set_line_style(int style)
    {
        eggx_newlinestyle(this->win_num, style);
    }

    void set_gcfunction(int fnc)
    {
        eggx_newgcfunction(this->win_num, fnc);
    }

    void move_pen(double x, double y)
    {
        this->penx = x;
        this->peny = y;
        eggx_line(this->win_num, x, y, pen_mode);
    }

    void draw_circle(double x, double y, double xrad, double yrad, bool fill = true, double sang = 0, double eang = 360, int idir = 1)
    {
        if (fill)
            eggx_fillarc(this->win_num, x, y, xrad, yrad, sang, eang, idir);
        else
            eggx_drawarc(this->win_num, x, y, xrad, yrad, sang, eang, idir);
    }

    /// x, y = penx, peny
    void draw_circle(double xrad, double yrad, bool fill = true, double sang = 0, double eang = 360, int idir = 1)
    {
        if (fill)
            eggx_fillarc(this->win_num, this->penx, this->peny, xrad, yrad, sang, eang, idir);
        else
            eggx_drawarc(this->win_num, this->penx, this->peny, xrad, yrad, sang, eang, idir);
    }

    void draw_rect(double x1, double y1, double width, double height, bool fill = true)
    {
        if (fill)
            eggx_fillrect(this->win_num, x1, y1, width, height);
        else
            eggx_drawrect(this->win_num, x1, y1, width, height);
    }

    void draw_poly(double x[], double y[], int n, int i = 0)
    {
        eggx_fillpoly(this->win_num, x, y, n, i);
    }

    void draw_arrow(double xs, double ys, double xt, double yt, double s, double w, int i, int j)
    {
        eggx_drawarrow(this->win_num, xs, ys, xt, yt, s, w, i * 10 + j);
    }

    /// xs, ys = penx, peny
    void draw_arrow(double xt, double yt, double s, double w, int i, int j)
    {
        eggx_drawarrow(this->win_num, this->penx, this->peny, xt, yt, s, w, i * 10 + j);
    }

    void draw_text(int size, const char *args, double x, double y)
    {
        eggx_drawstr(this->win_num, x, y, size, 0.0, args);
    }

    /// x, y = penx, peny
    void draw_text(int size, const char *args)
    {
        eggx_drawstr(this->win_num, this->penx, this->peny, size, 0.0, args);
    }

    void set_font(const char *font)
    {
        eggx_newfontset(this->win_num, font);
    }

    void scroll(int inc_x, int inc_y, int clr)
    {
        eggx_gscroll(this->win_num, inc_x, inc_y, clr);
    }

    void copy_from(double x, double y, int src_wn, int src_ly, double src_xs, double src_ys, double src_xe, double src_ye)
    {
        eggx_gputarea(this->win_num, x, y, src_wn, src_ly, src_xs, src_ys, src_xe, src_ye);
    }

    int put_image(double x, double y, unsigned char *buf, int width, int height, int msk)
    {
        return eggx_gputimage(this->win_num, x, y, buf, width, height, msk);
    }

    unsigned char *get_image(int ly, double xs, double ys, double xe, double ye, int *r_width, int *r_height)
    {
        return eggx_ggetimage(this->win_num, ly, xs, ys, xe, ye, r_width, r_height);
    }

    int save_image(int ly, double xs, double ys, double xe, double ye, const char *filter, int depth, const char *file_name)
    {
        return eggx_gsaveimage(this->win_num, ly, xs, ys, xe, ye, filter, depth, file_name);
    }

    unsigned char *read_image(const char *filter, const char *filename, int *r_width, int *r_height, int *r_msk)
    {
        return eggx_readimage(filter, filename, r_width, r_height, r_msk);
    }

    int write_image(const unsigned char *buf, int width, int height, int msk, const char *filter, int depth, const char *filename)
    {
        return eggx_writeimage(buf, width, height, msk, filter, depth, filename);
    }

    /// DISABLE = 0, ENABLE = -1
    void set_non_block(int flag)
    {
        eggx_gsetnonblock(flag);
    }

    static int get_key()
    {
        return eggx_ggetch();
    }

    void get_key_click(int *type, int *button, double *x, double *y)
    {
        int ltype, lbutton;
        double lx, ly;
        int wn = 0;
        while (wn != this->win_num)
        {
            wn = eggx_ggetxpress(&ltype, &lbutton, &lx, &ly);
        }
        *type = ltype;
        *button = lbutton;
        *x = lx;
        *y = ly;
    }

    static void sleep(unsigned long mills)
    {
        eggx_msleep(mills);
    }

    Weggx(WindowInfo wininfo, const char *win_title = DEFAULT_WINDOW_NAME)
    {
        this->win_info = wininfo;
        this->win_num = eggx_gopen(this->win_info.width, this->win_info.height);
        eggx_winname(this->win_num, win_title);
        eggx_layer(this->win_num, 0, 1);
    }

    Weggx(const char *win_title = DEFAULT_WINDOW_NAME)
    {
        int depth, width, height;
        eggx_ggetdisplayinfo(&depth, &width, &height);
        this->win_info = WindowInfo{depth, width, height};
        this->win_num = eggx_gopen(win_info.width, win_info.height);
        eggx_winname(this->win_num, win_title);
        eggx_layer(this->win_num, 0, 1);
    }
};

#endif // WEGGX_HPP