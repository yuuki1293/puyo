#ifndef MINESWEEPER_CORE_HPP
#define MINESWEEPER_CORE_HPP

#include <vector>
#include <algorithm>

class MSCore
{
private:
    std::vector<std::vector<int>> cell;
public:
    MSCore();
    ~MSCore();
};

MSCore::MSCore(/* args */)
{
}

MSCore::~MSCore()
{
}


#endif//MINESWEEPER_CORE_HPP