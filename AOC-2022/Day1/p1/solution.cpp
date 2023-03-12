// aoc
// Day1-p1 
// 
// Date: Thursday December 01, 2022
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
    
    std::string sep{ "" };

    auto ans = rng::max(
        rng::getlines(std::cin)
        | rv::split(sep)
        | rv::transform([](auto &&rng) {
            return rng::accumulate(
                rng
                | rv::transform([](auto &&el) {
                    return std::stoi(el);
                }),
                0
            );
        })
    );

    std::cout << ans << std::endl;
}
