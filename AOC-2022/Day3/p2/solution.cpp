// AOC-2022
// Day3-p2 
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

template <typename T>
class GetType;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto ans = rng::istream_view<std::string>(std::cin)
        | rv::chunk(3)
        | rv::transform([](auto &&chunk) {
            auto elfs_runsacks = chunk | rng::to<std::vector>();

            auto &first_elf = elfs_runsacks[0];
            auto &second_elf = elfs_runsacks[1];
            auto &third_elf = elfs_runsacks[2];

            rng::sort(first_elf);
            rng::sort(second_elf);
            rng::sort(third_elf);

            std::string first_two_common;
            std::string badge;

            rng::set_intersection(first_elf, second_elf, std::back_inserter(first_two_common));
            rng::set_intersection(third_elf, first_two_common, std::back_inserter(badge));
            
            return badge[0];
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
