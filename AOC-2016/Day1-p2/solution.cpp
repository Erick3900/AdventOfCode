// AOC-2016
// Day1-p2 
// 
// Date: Sunday November 27, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

// #define _DEBUG

#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

namespace rng = ranges;
namespace rv = ranges::views;

template <>
struct std::hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<uint64_t>{}((static_cast<uint64_t>(p.first) << 32) | static_cast<uint64_t>(p.second));
    }
};

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::string input;
    std::getline(std::cin, input);

    constexpr std::string_view delim{ ", " };

    auto transformed_input = input 
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

    std::unordered_set<decltype(curr_position)> unique_coords;

    unique_coords.insert(curr_position);

    for (const auto &[dir, len] : transformed_input) {
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

        for (auto _ : rv::ints(0, len)) {
            x += off_x;
            y += off_y;
            
            auto [iter, success] = unique_coords.insert(curr_position);

            if (! success) {
                std::cout << (std::abs(x) + std::abs(y)) << std::endl;
                return 0;
            }
        }
    }

    const auto &[x,y] = curr_position;

    std::cout << (std::abs(x) + std::abs(y)) << std::endl; 
}

/*
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * . * * * * * * * * *
 * * * * * * * * * * * * * * . * * * * * * * * *
 * * * * * * * * * * * * * * . * * * * * * * * *
 * * * * * * * * * * . . . . . . . . . * * * * *
 * * * * * * * * * * * * * * . * * * . * * * * *
 * * * * * * * * * * * * * * . * * * . * * * * *
 * * * * * * * * * * * * * * . * * * . * * * * *
 * * * * * * * * * * * * * * . . . . . * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * *
 * */
