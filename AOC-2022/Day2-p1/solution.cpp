// AOC-2022
// Day2-p1 
// 
// Date: Friday December 02, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <range/v3/all.hpp>
#include <range/v3/view/istream.hpp>

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

namespace rng = ranges;
namespace rv = rng::views;

template <typename T>
class GetType;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    const std::unordered_map<char, int> values{
        { 'X', 0 }, // Rock
        { 'Y', 1 }, // Paper
        { 'Z', 2 }, // Scissors
        { 'A', 0 },
        { 'B', 1 },
        { 'C', 2 }
    };

    /*
     * 0 -> 2
     * 1 -> 0
     * 2 -> 1
     * */

    auto ans = rng::istream_view<std::string>(std::cin)
        | rv::transform([](std::string_view &&el) {
            return el[0];
        })
        | rv::chunk(2)
        | rv::transform([&](auto &&strategy) {
            const auto choice = strategy | rng::to<std::vector>();
            
            const auto p1 = values.at(choice[0]);
            const auto p2 = values.at(choice[1]);

            // Draw
            if (p2 == p1) {
                return 4 + p2;
            }

            // Win
            if (p1 == ((p2 + 2) % 3)) {
                return 7 + p2;
            }
            
            // Loose
            return 1 + p2;
        })
    ;

    std::cout << rng::accumulate(ans, 0) << std::endl;

}
