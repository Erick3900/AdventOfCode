// AOC-2022
// Day15-p1 
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

    auto manhattanDistance = [](int fx, int fy, int tx, int ty) {
        return std::abs(tx - fx) + std::abs(ty - fy);
    };

    const int target_line = 2000000;

    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();

    std::unordered_set<int> beaconsAtTarget;

    auto input = rng::getlines(std::cin)
        | rv::transform([&beaconsAtTarget](std::string line) {
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

            auto beacon = std::get<1>(data);

            if (beacon.second == target_line) {
                beaconsAtTarget.insert(beacon.first);
            }

            return data;
        })
        | rv::filter([&](auto &&data) {
            const auto &[sensor, beacon] = data;
            const auto &[s_x, s_y] = sensor;
            const auto &[b_x, b_y] = beacon;

            auto dist = manhattanDistance(s_x, s_y, b_x, b_y);

            return std::abs(target_line - s_y) <= dist;
        })
        | rv::transform([&](auto &&data) {
            const auto &[sensor, beacon] = data;
            const auto &[s_x, s_y] = sensor;
            const auto &[b_x, b_y] = beacon;

            auto dist = manhattanDistance(s_x, s_y, b_x, b_y);
            auto diff = dist - std::abs(target_line - s_y);

            auto range = std::pair{ s_x - diff, s_x + diff };

            minX = std::min(minX, range.first);
            maxX = std::max(maxX, range.second);

            return range;
        })
        | rng::to<std::vector>()
    ;

    std::vector<bool> row(maxX - minX + 1, false);

    for (const auto &[stx, lsx] : input) {
        int fX = stx - minX;
        int sX = lsx - minX + 1;

        for (; fX < sX; ++fX) {
            row[fX] = true;
        }
    }

    int ans = 0;

    for (int i = 0;  i < row.size(); ++i) {
        if (row[i] && !beaconsAtTarget.contains(minX + i)) {
            ans++;
        }
    }

    std::cout << ans << std::endl;
}
