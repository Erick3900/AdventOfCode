// AOC-2022
// Day15-p2 
// 
// Date: Thursday December 15, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

#define _DEBUG
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

    constexpr const int LIMIT = 4000000;

    auto manhattanDistance = [](int fx, int fy, int tx, int ty) {
        return std::abs(tx - fx) + std::abs(ty - fy);
    };

    auto input = rng::getlines(std::cin)
        | rv::transform([&](std::string line) {
            std::regex inputParser{ 
                "(Sensor at x=)(-?\\d+)(, y=)(-?\\d+)(: closest beacon is at x=)(-?\\d+)(, y=)(-?\\d+)",
                std::regex_constants::ECMAScript |
                std::regex_constants::multiline
            };

            std::smatch match;

            std::regex_match(line, match, inputParser);

            std::tuple<std::pair<int, int>, std::pair<int, int>> data;

            data = {
                std::pair{ std::stoi(match.str(2)), std::stoi(match.str(4)) },
                std::pair{ std::stoi(match.str(6)), std::stoi(match.str(8)) }
            };

            return data;
        })
        | rng::to<std::vector>()
    ;

    auto isInside = [](auto &data) {


        return true;
    };

    for (int i = 0; i < input.size(); ++i) {
        auto [s_x, s_y] = std::get<0>(input[i]);
        auto [b_x, b_y] = std::get<1>(input[i]);

        auto dist = manhattanDistance(s_x, s_y, b_x, b_y);

        int c_x = s_x;
        int c_y = std::max(s_y - dist - 1, 0);

        for (int y = c_y, x = c_x; y < std::max(s_y, LIMIT); ++y, ++x) {
            auto inside = [&]() {
                for (int j = i + 1; j < input.size(); ++j) {
                    if (isInside(input[i])) {
                        return true;
                    }
                }

                return false;
            }();

            if (! inside) {
                // std::cout << (x * LIMIT + y) << std::endl;
            }
        }
    }
}
