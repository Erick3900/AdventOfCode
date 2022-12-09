// AOC-2022
// Day8-p1 
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

    std::vector<std::vector<bool>> visible(tree_grid.size(), std::vector<bool>(tree_grid.size(), false));

    int ans = 0;

    for (int i = 0; i < tree_grid.size(); ++i) { 
        int l_curr_max = std::numeric_limits<int>::min();
        int r_curr_max = std::numeric_limits<int>::min();
        int t_curr_max = std::numeric_limits<int>::min();
        int b_curr_max = std::numeric_limits<int>::min();

        for (int j = 0; j < tree_grid.size(); ++j) {
            if (tree_grid[i][j] > l_curr_max) {
                l_curr_max = tree_grid[i][j];
                
                visible[i][j] = true;
            }

            if (tree_grid[i][tree_grid.size() - j - 1] > r_curr_max) {
                r_curr_max = tree_grid[i][tree_grid.size() - j - 1];
                
                visible[i][tree_grid.size() - j - 1] = true;
            }

            if (tree_grid[j][i] > t_curr_max) {
                t_curr_max = tree_grid[j][i];
                
                visible[j][i] = true;
            }

            if (tree_grid[tree_grid.size() - j - 1][i] > b_curr_max) {
                b_curr_max = tree_grid[tree_grid.size() - j - 1][i];
                
                visible[tree_grid.size() - j - 1][i] = true;
            }           
        }
    }

    for (const auto &row : visible) {
        for (const auto &v : row) {
            if (v) {
                ++ans;
            }
        }
    }

    std::cout << ans << std::endl;
}
