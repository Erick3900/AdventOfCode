// AOC-2016
// Day2-p1 
// 
// Date: Sunday November 27, 2022
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

template <typename T>
class TypeGetter;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    const std::array<std::array<int, 3>, 3> keypad{
        std::array{ 1, 2, 3 },
        std::array{ 4, 5, 6 },
        std::array{ 7, 8, 9 }
    };

    int x = 1;
    int y = 1;

    auto input = rng::istream_view<std::string>(std::cin)
      | rv::transform([&keypad, &x, &y](auto &&rng) {
            for (const auto &c : rng) {
                switch(c) {
                    case 'U':
                        y = std::max(0, y - 1);
                        break;
                    case 'D':
                        y = std::min(2, y + 1);
                        break;
                    case 'L':
                        x = std::max(0, x - 1);
                        break;
                    case 'R':
                        x = std::min(2, x + 1);
                        break;
                }
            }

            return '0' + keypad[y][x];
        })
      | rng::to<std::string>();

      std::cout << input << std::endl;
}

