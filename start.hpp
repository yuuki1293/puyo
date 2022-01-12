#ifndef START_HPP
#define START_HPP

#include <tuple>
#include "weggx.hpp"

class Start
{
public:
    static std::tuple<int, int, int> start(Weggx *weggx)
    {
        weggx->set_window_size(500, 1000);
        weggx->drow_text(30,"mine sweeper",50,100);

        weggx->show();
        return std::make_tuple(50,50,50);
    }
};

#endif // START_HPP