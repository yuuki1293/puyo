#ifndef MINESWEEPER_CORE_HPP
#define MINESWEEPER_CORE_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

struct posi
{
    int row;
    int column;
    bool is_neighbor(posi r) // NOTE 使わないかもしれない
    {
        int row_dist = abs(r.row - row);
        int colum_dist = abs(r.column - column);
        if (row_dist <= 1)
            if (colum_dist <= 1)
                return true;
        return false;
    }
    bool operator==(const posi x) { return row == x.row && column == x.column; }
    bool operator!=(const posi x) { return row != x.row || column != x.column; }
};

class MSCore
{
private:
    std::vector<posi> bombs;
    std::vector<posi> flags;
    std::vector<std::vector<bool>> opened;
    int cells_count() { return row * column; }
    int row, column;
    std::random_device seed_gen;
    // 0:プレイ中 1:ゲームオーバー 2:クリア
    int status;
public:
    // -3:もう開いてるよ -2:旗だよ -1:爆弾だよ 0~:周りの爆弾の数だよ
    int click(posi cell)
    {
        if (opened[cell.row][cell.column])
            return -3;
        for (size_t i = 0; i < flags.size(); i++)
            if (flags[i] == cell)
                return -2;
        for (size_t i = 0; i < bombs.size(); i++)
            if (bombs[i] == cell)
                return -1;
        opened[cell.row][cell.column] = true;
        int neighbor_boms_count = 0;
        for (size_t i = 0; i < bombs.size(); i++)
            if (cell.is_neighbor(bombs[i]))
                neighbor_boms_count++;
        return neighbor_boms_count;
    }
    MSCore(int, int, int);
    ~MSCore();
};

MSCore::MSCore(int column, int row, int bomb_num)
{
    if (row * column <= bomb_num)
        throw std::runtime_error("爆弾の数がセルの数と同じかそれより多いよ!");

    this->row = row;
    this->column = column;
    std::random_device rd;
    std::default_random_engine engine(seed_gen());

    using hash_map = std::unordered_map<int, int>;

    std::vector<int> tmp;
    tmp.reserve(bomb_num);
    hash_map Map;
    int rand_max = column * row - 1;
    for (int i = 0; i < bomb_num; i++)
    {
        auto val = std::uniform_int_distribution<>(0, rand_max)(engine);
        hash_map::iterator itr = Map.find(val);

        int replaced_val;
        hash_map::iterator replaced_itr = Map.find(rand_max);
        if (replaced_itr != Map.end())
            replaced_val = replaced_itr->second;
        else
            replaced_val = rand_max;

        if (itr == Map.end())
        {
            tmp.push_back(val);
            if (val != rand_max)
                Map.insert(std::make_pair(val, replaced_val));
        }
        else
        {
            tmp.push_back(itr->second);
            itr->second = replaced_val;
        }
        rand_max--;
    }

    for (int i = 0; i < bomb_num; i++)
    {
        int r = tmp[i] / row;
        int c = tmp[i] % column;
        bombs[i] = posi{r, c};
    }
}

MSCore::~MSCore()
{
}

#endif // MINESWEEPER_CORE_HPP