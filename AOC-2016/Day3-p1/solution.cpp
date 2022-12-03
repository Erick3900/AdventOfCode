// AOC-2016
// Day3-p1 
// 
// Date: Monday November 28, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <bits/utility.h>
#include <range/v3/all.hpp>

#define _DEBUG
#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

template <typename T, size_t... I>
auto tuple_converter(T&& rng, std::index_sequence<I...>) {
    return std::make_tuple(rng[I]...);
}

namespace rng = ranges;
namespace rv = ranges::views;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto ans = rng::istream_view<int>(std::cin)
      | rv::chunk(3)
      | rv::transform([](auto &&tri)-> bool {
            const auto values = tri | rng::to<std::vector>();

            const auto &l1 = values[0];
            const auto &l2 = values[1];
            const auto &l3 = values[2];

            return ((l1 + l2) > l3) && ((l2 + l3) > l1) && ((l1 + l3) > l2);
        })
      | rng::to<std::vector>();

    std::cout << (rng::count_if(ans, [](auto &&v) { return v; })) << std::endl;
}
