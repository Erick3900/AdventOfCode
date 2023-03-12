// AOC-2015
// Day1-p2 
// 
// Date: Saturday November 26, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x, y)
#    define debug(x)
#endif

namespace rng = ranges;
namespace rv = rng::views;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);
 
    std::string line;

    std::getline(std::cin, line);

    int64_t n_instruction = 0;
    int64_t current_floor = 0;

    for (auto &c : line) {
        ++n_instruction;

        switch(c) {
            case '(':
                ++current_floor;
                break;
            case ')':
                --current_floor;
                break;
        }
        
        if (current_floor < 0) {
            std::cout << n_instruction << std::endl;
            return 0;
        }
    }

    std::cout << n_instruction << std::endl;
}
