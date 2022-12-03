// AOC-2016
// Day1-p1 
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

    std::string input;
    std::getline(std::cin, input);

    constexpr std::string_view delim{ ", " };

    auto res = input 
      | rv::split(delim)
      | rv::transform([](auto &&rng) {
            const auto instruction = rng | rng::to<std::string>();
            return std::pair{ instruction[0], std::stoi(instruction.substr(1)) };
        })
      | rng::to<std::vector>();

    const std::vector<std::pair<int, int>> directions{ 
        std::pair{  0, -1 }, //    UP
        std::pair{  1,  0 }, // RIGHT
        std::pair{  0,  1 }, //  DOWN
        std::pair{ -1,  0 }  //  LEFT
    };

    int8_t curr_direction = 0;
    std::pair<int, int> curr_position = { 0, 0 };

    for (const auto &[dir, len] : res) {
        if (dir == 'L') {
            curr_direction = ((curr_direction - 1) % 4 + 4) % 4;
        }
        else if (dir == 'R') {
            curr_direction = (curr_direction + 1) % 4;
        }
        else {
            throw std::runtime_error("What?");
        }

        auto &[x, y] = curr_position;
        const auto &[off_x, off_y] = directions[curr_direction];

        x += (off_x * len);
        y += (off_y * len);
    }

    const auto &[x,y] = curr_position;

    std::cout << (std::abs(x) + std::abs(y)) << std::endl; 
}
