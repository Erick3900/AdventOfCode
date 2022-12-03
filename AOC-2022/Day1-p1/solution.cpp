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
    
    std::string sep{ "" };

    std::vector<std::string> input;

    std::string line;

    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }

    auto ans = rng::max(input
        | rv::split(sep)
        | rv::transform([](auto &&rng) {
            return rng::accumulate((rng
                | rv::transform([](auto &&el) {
                    return std::stoi(el);
                })),
                0
            );
        }));

    std::cout << ans << std::endl;
}
