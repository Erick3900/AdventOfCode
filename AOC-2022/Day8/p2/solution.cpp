// AOC-2022
// Day8-p2 
// 
// Date: Thursday December 08, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#define _DEBUG
#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { x };
#else
#    define deb(x)
#    define deb2(x, y)
#    define debug(x)
#endif

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::vector<std::string> tree_grid = []() {     
        std::vector<std::string> ret_val;

        std::string row;

        while (std::getline(std::cin, row)) {
            ret_val.push_back(row);
        }
        
        return ret_val;
    }();

    int max_score = -1;

    for (int i = 0; i < tree_grid.size(); ++i) {
        for (int j = 0; j < tree_grid.size(); ++j) {
            int l_count = [&](int x, int y) {
                while (x > 0 && tree_grid[y][x] < tree_grid[i][j]) {
                    --x;
                }

                if (x < 0) 
                    ++x;

                return j - x;
            }(j - 1, i);

            int r_count = [&](int x, int y) {
                while (x < tree_grid.size() && tree_grid[y][x] < tree_grid[i][j]) {
                    ++x;
                }

                if (x == tree_grid.size())
                    --x;

                return x - j;
            }(j + 1, i);

            int t_count = [&](int x, int y) {
                while (y > 0 && tree_grid[y][x] < tree_grid[i][j]) {
                    --y;
                }

                if (y < 0)
                    ++y;

                return i - y;
            }(j, i - 1);

            int b_count = [&](int x, int y) {
                while (y < tree_grid.size() && tree_grid[y][x] < tree_grid[i][j]) {
                    ++y;
                }

                if (y == tree_grid.size())
                    --y;

                return y - i;
            }(j, i + 1);

            int curr_score = (l_count * r_count * t_count * b_count);

            max_score = std::max(max_score, curr_score);
        }
    }

    std::cout << max_score << std::endl;
}
