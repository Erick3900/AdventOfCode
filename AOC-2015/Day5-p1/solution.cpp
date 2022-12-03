// AOC-2015
// Day5-p1 
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

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto input = rng::istream_view<std::string>(std::cin)
      | rv::filter([](auto &&str) -> bool {
            auto vowels = rv::filter(str, 
                [](auto &&c) {
                    static const std::string vowels{ "aeiou" };

                    return vowels.find(c) != std::string::npos;
                }
            ) | rng::to<std::string>();

            return rng::size(vowels) >= 3;
        })
      | rv::filter([](auto &&str) -> bool {
            return rng::adjacent_find(str) != str.end();
        })
      | rv::filter([](auto &&str) -> bool {
            static const std::vector<std::string> not_allowed{ "ab", "cd", "pq", "xy" };

            return rng::all_of(not_allowed, [&](const auto &pattern) -> bool {
                const std::string str_val = str | rng::to<std::string>();;

                return str_val.find(pattern) == std::string::npos;
            });
        })
      | rng::to<std::vector>();

    std::cout << input.size() << std::endl;
}
