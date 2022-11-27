// AOC-2015
// Day2-p1 
// 
// Date: Saturday November 26, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <fmt/format.h>
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

struct box {
    int32_t length;
    int32_t width;
    int32_t height;
};

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);


    auto input = ranges::istream_view<std::string>(std::cin)
      | ranges::views::transform([](auto &&el) {
            constexpr std::string_view delim{ "x" };
            return ranges::split_view(el, delim);
        })
      | ranges::views::transform([](auto &&el) {
            return ranges::transform_view(el, [](auto &&el) {
                return std::stoi(el | ranges::to<std::string>());
            });
        })
      | ranges::views::transform([](auto &&el) {
            const auto vec = el | ranges::to<std::vector>();
            return box{ vec[0], vec[1], vec[2] };
        });

    // 2*l*w + 2*w*h + 2*h*l
    
    int64_t total_paper = 0;

    for (const auto &b : input) {
        const auto side_1 = b.width  * b.length;
        const auto side_2 = b.width  * b.height;
        const auto side_3 = b.height * b.length;

        total_paper += (side_1 * 2);
        total_paper += (side_2 * 2);
        total_paper += (side_3 * 2);
        total_paper += std::min({ side_1, side_2, side_3 });
    }

    std::cout << total_paper << std::endl;
}
