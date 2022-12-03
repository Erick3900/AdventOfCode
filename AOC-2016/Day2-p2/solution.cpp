// AOC-2016
// Day2-p2 
// 
// Date: Sunday November 27, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

#define _DEBUG
#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    const std::vector<std::vector<char>> keypad{
        std::vector{ ' ', ' ', '1', ' ', ' ' },
        std::vector{ ' ', '2', '3', '4', ' ' },
        std::vector{ '5', '6', '7', '8', '9' },
        std::vector{ ' ', 'A', 'B', 'C', ' ' },
        std::vector{ ' ', ' ', 'D', ' ', ' ' }
    };

    int x = 0;
    int y = 2;

    auto input = ranges::istream_view<std::string>(std::cin)
      | ranges::views::transform([&keypad, &x, &y](auto &&rng) {
            const auto constraint_pos = [](auto &x, auto &y) {
                const auto constraint_val = std::abs(2 - y);
                return std::clamp(x + 1, constraint_val, 4 - constraint_val);
            }; 

            const auto constraint_neg = [](auto &x, auto &y) {
                const auto constraint_val = std::abs(2 - y);
                return std::clamp(x - 1, constraint_val, 4 - constraint_val);
            };

            for (const auto &c : rng) {
                switch(c) {
                    case 'L': x = constraint_neg(x, y); break;
                    case 'U': y = constraint_neg(y, x); break;
                    case 'R': x = constraint_pos(x, y); break;
                    case 'D': y = constraint_pos(y, x); break;
                }
            }

            return keypad[y][x];
        })
      | ranges::to<std::string>();

    std::cout << input << std::endl;
}

