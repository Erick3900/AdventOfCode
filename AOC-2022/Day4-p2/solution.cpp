// AOC-2022
// Day4-p2 
// 
// Date: Sunday December 04, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

// #define _DEBUG
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

template <typename T, size_t... I>
auto helper(T&& rng, std::index_sequence<I...>) {
    return std::make_tuple(rng[I]...);
}

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto ans = rng::istream_view<std::string>(std::cin)
        | rv::transform([](std::string line) {
            constexpr std::string_view sep_elfs{ "," };
            constexpr std::string_view sep_nums{ "-" };

            auto [f_elf, s_elf] = helper(
                line 
                    | rv::split(sep_elfs)
                    | rv::transform([](auto &&rng) {
                        return rng | rng::to<std::string>();
                    })
                    | rng::to<std::vector>(),
                std::make_index_sequence<2>()
            );

            const auto [lb_e1, ub_e1] = helper(
                f_elf
                    | rv::split(sep_nums)
                    | rv::transform([](auto &&rng) {
                        return std::stoi(rng | rng::to<std::string>());
                    })
                    | rng::to<std::vector>(),
                std::make_index_sequence<2>()
            );

            const auto [lb_e2, ub_e2] = helper(
                s_elf
                    | rv::split(sep_nums)
                    | rv::transform([](auto &&rng) {
                        return std::stoi(rng | rng::to<std::string>());
                    })
                    | rng::to<std::vector>(),
                std::make_index_sequence<2>()
            );

            deb2(lb_e1, ub_e1);
            deb2(lb_e2, ub_e2);

            const auto checkOverlap = [](int lb, int ub, int v) {
                return lb <= v && v <= ub;
            };

            return (
                checkOverlap(lb_e1, ub_e1, lb_e2) ||
                checkOverlap(lb_e1, ub_e1, ub_e2) ||
                checkOverlap(lb_e2, ub_e2, lb_e1) ||
                checkOverlap(lb_e2, ub_e2, ub_e1)
            );
        })
    ;

    std::cout << rng::count_if(ans, [](auto cond){ return cond; }) << std::endl;
}
