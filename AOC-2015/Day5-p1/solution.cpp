// AOC-2015
// Day5-p1 
// 
// Date: Sunday November 27, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto input = ranges::istream_view<std::string>(std::cin)
      | ranges::views::filter([](auto &&str) -> bool {
            auto vowels = ranges::views::filter(str, [](auto &&c) {
                static const std::string vowels{ "aeiou" };
                return vowels.find(c) != std::string::npos;
            }) | ranges::to<std::string>();

            return ranges::size(vowels) >= 3;
        })
      | ranges::views::filter([](auto &&str) -> bool {
            return ranges::adjacent_find(str) != str.end();
        })
      | ranges::views::filter([](auto &&str) -> bool {
            static const std::vector<std::string> not_allowed{ "ab", "cd", "pq", "xy" };

            return ranges::all_of(not_allowed, [&](const auto &pattern) -> bool {
                const std::string str_val = str | ranges::to<std::string>();;

                return str_val.find(pattern) == std::string::npos;
            });
        })
      | ranges::to<std::vector>();

    std::cout << input.size() << std::endl;
}
