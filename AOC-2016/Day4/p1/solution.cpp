// AOC-2016
// Day4-p1 
// 
// Date: Monday November 28, 2022
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
struct GetType;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto input = rng::istream_view<std::string>(std::cin) 
        | rv::transform([](auto &&rng) {
            constexpr std::string_view sep{ "-" };

            auto splitted_range = rng
                | rv::split(sep)
                | rv::transform([](auto &&str) { 
                    return str
                        | rng::to<std::string>(); 
                })
                | rng::to<std::vector>();
            
            auto mapped = splitted_range
                | rv::drop_last(1)
                | rv::join
                | rng::to<std::string>();

            return std::pair{ 
                mapped, 
                splitted_range.back()
            };
        })
        | rng::to<std::vector>();

    int64_t total_id_sum = 0;

    for (const auto &[room_name, checksum] : input) {
        std::unordered_map<char, int> frequencies;
        for (const auto &c : room_name) {
            ++frequencies[c];
        }

        auto values = frequencies
            | rv::transform([](auto &&el) {
                return std::pair<char, int>{ el.first, el.second };
            })
            | rng::to<std::vector>();

        rng::sort(values, [](const auto &char1, const auto &char2) {
            if (char1.second != char2.second) {
                return char1.second > char2.second;
            }
            else return char1.first < char2.first;
        });

        auto bracket_pos = checksum.find('[');
        const int id = std::stoi(checksum.substr(0, bracket_pos));
        const std::string checksum_letters = checksum.substr(bracket_pos + 1, 5);

        bool real_room = true;

        for (int i = 0; const auto &c : checksum_letters) {
            if (c != values[i++].first) {
                real_room = false;
                break;
            }
        }

        if (real_room) {
            total_id_sum += id;
        }
    }

    std::cout << total_id_sum << std::endl;
}
