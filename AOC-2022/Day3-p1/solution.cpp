// AOC-2022
// Day3-p1 
// 
// Date: Saturday December 03, 2022
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

    auto ans = rng::istream_view<std::string>(std::cin)
        | rv::transform([](std::string line) {
            auto first_half = line.substr(0, line.size() >> 1);
            auto second_half = line.substr(line.size() >> 1);

            rng::sort(first_half);
            rng::sort(second_half);

            std::string output;

            rng::set_intersection(first_half, second_half, std::back_inserter(output));

            return output[0];
        })
        | rv::transform([](char c) {
            if (c >= 'a' && c <= 'z') {
                return c - 'a' + 1;
            }
            else {
                return c - 'A' + 27;
            }
        })
    ;

    std::cout << rng::accumulate(ans, 0) << std::endl;
}
