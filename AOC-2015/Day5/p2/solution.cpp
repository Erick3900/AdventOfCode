// AOC-2015
// Day5-p2 
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

template <typename T, size_t... I>
auto tuple_converter(T&& rng, std::index_sequence<I...>) {
    return std::make_tuple(rng[I]...);
}

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto input = rng::istream_view<std::string>(std::cin)
      | rv::filter([](auto &&str) -> bool {
            int32_t n = 0;
    
            for (const auto &window : str | rv::sliding(2)) {
                for (const auto &rng : str | rv::drop(n + 2) | rv::sliding(2)) {
                    if (rng::equal(window, rng)) {
                        return true;
                    }
                }
                ++n;
            }
        
            return false;
        })
      | rv::filter([](auto &&str) -> bool {
            for (const auto &window : str | rv::sliding(3)) {
                const auto [first, second, third] = tuple_converter(window, std::make_index_sequence<3>{});

                if (first == third)
                    return true;
            }

            return false;
        })
      | rng::to<std::vector>()
    ;

    std::cout << input.size() << std::endl;
}
