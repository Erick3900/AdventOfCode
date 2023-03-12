// AOC-2022
// Day5-p1 
// 
// Date: Monday December 05, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

namespace rng = ranges;
namespace rv = rng::views;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    constexpr const size_t N_STACKS = 9;

    std::string line;

    bool not_break = true;

    std::vector<std::string> cargo;

    do {
        std::getline(std::cin, line);

        if (line.empty()) {
            not_break = false;
            continue;
        }

        auto processed_line = line
            | rv::chunk(4)
            | rv::transform([](auto chunk) {
                auto sz = rng::size(chunk);
                
                const auto element = chunk
                    | rv::drop_last(sz == 4 ? 2 : 1)
                    | rv::drop(1);

                return *element.begin();
            })
            | rng::to<std::string>()
        ;

        cargo.push_back(processed_line);
    } while (not_break);

    const auto helper = []<typename Rng, size_t ...I>
        (Rng &&rng, std::index_sequence<I...>) {
            return rng::zip_view(rng.at(sizeof...(I) - I - 1)...)
                | rv::transform([](auto tuple) {
                    const auto to_string_helper = []<typename Tuple, size_t ...J>
                        (Tuple &&tup, std::index_sequence<J...>) {
                            return std::string{ std::get<J>(tup)... };
                        };

                    return to_string_helper(tuple, std::make_index_sequence<N_STACKS>());
                });
        };

    std::map<int, std::stack<char>> stacks;

    for (const auto &st : helper(cargo, std::make_index_sequence<N_STACKS>())) {
        auto &stack = stacks[st[0] - '0'];

        for (size_t i = 1; i < st.size(); ++i) {
            if (st[i] != ' ')
                stack.push(st[i]);
        }
    }

    while (std::getline(std::cin, line)) {
        constexpr std::string_view sep{ " " };

        auto input = rv::zip(line | rv::split(sep), rv::iota(0))
            | rv::filter([](auto c) {
                return ((std::get<1>(c) % 2) == 1);
            })
            | rv::transform([](auto c) {
                return std::get<0>(c);
            })
            | rv::transform([](auto n) {
                return std::stoi(n | rng::to<std::string>());
            })
            | rng::to<std::vector>();
        ;

        int n = input[0];
        auto &s_from = stacks[input[1]];
        auto &s_to = stacks[input[2]];
    
        while (n--) {
            s_to.push(s_from.top());
            s_from.pop();
        }
    }

    for (auto &[_, stack] : stacks) {
        std::cout << stack.top();
    }

    std::cout << std::endl;
}
