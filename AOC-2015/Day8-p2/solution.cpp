// aoc
// Day8-p2 
// 
// Date: Monday November 28, 2022
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

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    const std::regex matchsticks{ 
        "[\\\\\"]",
        std::regex_constants::ECMAScript |
        std::regex_constants::multiline
    };

    auto input = rng::accumulate(rng::istream_view<std::string>(std::cin)
        | rv::transform([](auto &&rng) {
            return rng | rng::to<std::string>();
        })
        | rv::transform([&](std::string &&str) {
            const int code_len = str.length();
            const int str_len = [&str, &matchsticks]() -> int { 
                auto match_begin = std::sregex_iterator(str.begin(), str.end(), matchsticks);
                auto match_end = std::sregex_iterator();

                if (std::distance(match_begin, match_end) == 0) {
                    return str.length() + 2;
                }
                else {
                    std::smatch var_match;

                    int len = 2;

                    for (auto it = match_begin; it != match_end; ++it) {
                        var_match = *it;
                        len += var_match.prefix().length();
                        len += 2;
                        deb(var_match.str());
                    }
                    
                    return len + var_match.suffix().length();
                }
            }();

            deb2(str_len, code_len);
            return (str_len - code_len);
        }), 0
    );

    std::cout << input << std::endl;
}
