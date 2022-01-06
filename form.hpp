#ifndef SCENE_MANEGE_HPP
#define SCENE_MANEGE_HPP

#include "weggx.hpp"
#include <vector>
#include <functional>

class Form
{
protected:
    Weggx *weggx;
public:
    virtual void initialize() = 0;
    virtual void load() = 0;
    virtual ~Form() { delete weggx; }
};

#endif // SCENE_MANEGE_HPP