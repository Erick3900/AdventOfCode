// AOC-2015
// Day10-p2 
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

    std::string input;
    std::getline(std::cin, input);

    const auto algorithm = [](const std::string &in) -> std::string {
        int64_t count = 1;
        int64_t idx = 0;

        std::stringstream out;

        for (; idx < in.size(); ++idx) {
            const auto curr_char = in[idx];
            while (++idx < in.size() && curr_char == in[idx]) {
                count++;
            }

            out << count << curr_char;

            --idx;
            count = 1;
        }

        return out.str();
    };

    for (int i = 0; i < 50; ++i) {
        input = algorithm(input);
    }

    std::cout << input.length() << std::endl;
}
