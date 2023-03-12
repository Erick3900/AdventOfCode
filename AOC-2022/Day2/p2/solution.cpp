// AOC-2022
// Day2-p2 
// 
// Date: Friday December 02, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

namespace rng = ranges;
namespace rv = rng::views;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    const std::unordered_map<char, int> values{
        { 'X', 0 }, // Rock
        { 'Y', 1 }, // Paper
        { 'Z', 2 }, // Scissors
        { 'A', 0 },
        { 'B', 1 },
        { 'C', 2 }
    };

    /*
     * 0 -> 2
     * 1 -> 0
     * 2 -> 1
     * */

    auto ans = rng::istream_view<std::string>(std::cin)
        | rv::transform([](std::string_view &&el) {
            return el[0];
        })
        | rv::chunk(2)
        | rv::transform([&](auto &&strategy) {
            const auto choice = strategy | rng::to<std::vector>();
            
            const auto p1 = values.at(choice[0]);
            const auto p2 = values.at(choice[1]);

            switch(p2) {
                case 0: return 1 + ((p1 + 2) % 3); // Loose
                case 1: return 4 + ((p1 + 0) % 3); // Draw
                case 2: return 7 + ((p1 + 1) % 3); // Win
            }
            return 0;
        })
    ;

    std::cout << rng::accumulate(ans, 0) << std::endl;

}
