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
    bool is_neighbor(posi r)
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
    int opened_count = 0;
    int cells_count() { return row * column; }
    int row, column;
    std::random_device seed_gen;
    /// 0:プレイ中 1:ゲームオーバー 2:クリア
    int status;

public:
    /// -4:範囲外だよ -3:もう開いてるよ -2:旗だよ -1:爆弾だよ 0~:周りの爆弾の数だよ
    int left_click(posi cell);

    /// -4:範囲外だよ -3:もう開いてるよ 0:旗をつけたよ 1:旗を外したよ
    int right_click(posi cell);

    /// 0:プレイ中 1:ゲームオーバー 2:クリア
    int get_status();

    int get_rest_bomb();

    MSCore(int, int, int);
};

int MSCore::left_click(posi cell)
{
    //範囲外処理
    if (cell.row >= row || cell.row < 0 || cell.column >= column || cell.column < 0)
        return -4;

    //もう開いてるか
    if (opened[cell.row][cell.column])
        return -3;

    //旗が立っているか
    for (size_t i = 0; i < flags.size(); i++)
        if (flags[i] == cell)
            return -2;

    //爆弾か
    for (size_t i = 0; i < bombs.size(); i++)
        if (bombs[i] == cell)
        {
            status = 1; //フラグをゲームオーバーに設定
            return -1;
        }

    //クリア判定
    opened[cell.row][cell.column] = true;
    opened_count++;
    if (opened_count >= cells_count() - (int)bombs.size())
        status = 2; //フラグをクリアに設定

    //周りの爆弾の数
    int neighbor_boms_count = 0;
    for (size_t i = 0; i < bombs.size(); i++)
        if (cell.is_neighbor(bombs[i]))
            neighbor_boms_count++;
    return neighbor_boms_count;
}

int MSCore::right_click(posi cell)
{
    //範囲外処理
    if (cell.row >= row || cell.row < 0 || cell.column >= column || cell.column < 0)
        return -4;

    //もう開いてるか
    if (opened[cell.row][cell.column])
        return -3;

    //旗が立っているか
    for (size_t i = 0; i < flags.size(); i++)
        if (flags[i] == cell)
        {
            flags.erase(flags.begin() + i); //旗を削除
            return 1;
        }
    flags.push_back(cell); //旗を追加
    return 0;
}

inline int MSCore::get_status()
{
    return status;
}

inline int MSCore::get_rest_bomb()
{
    return bombs.size() - flags.size();
}

MSCore::MSCore(int row, int column, int bomb_num)
{
    if (row * column <= bomb_num)
        throw std::runtime_error("爆弾の数がセルの数と同じかそれより多いよ!");

    this->row = row;
    this->column = column;
    bombs.resize(bomb_num);
    opened.resize(row);
    for (int i = 0; i < row; i++)
        opened[i].resize(column);

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

#endif // MINESWEEPER_CORE_HPP