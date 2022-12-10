// AOC-2022
// Day10-p2 
// 
// Date: Saturday December 10, 2022
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

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    constexpr const std::string_view space{ " " };

    int register_x = 1;
    int n_cycle = 0;
    int curr_op_st = 0;
    int beam_pos = 0;

    std::vector<std::pair<std::string, int>> program;

    std::string line;
    while(std::getline(std::cin, line)) {
         auto instruction = line
            | rv::split(space)
            | rv::transform([](auto &&r){ 
                return r | rng::to<std::string>(); 
            })
            | rng::to<std::vector>();

        if (instruction[0] == "addx") {
            program.emplace_back(instruction[0], std::stoi(instruction[1]));
        }
        else {
            program.emplace_back(instruction[0], 0);
        }
    }

    const std::unordered_map<std::string, int> duration {
        std::pair{ "addx", 2 },
        std::pair{ "noop", 1 },
    };

    int ans = 0;

    std::cout << std::endl << "\t\t";

    for (int i = 0; i < program.size(); ++n_cycle) {       
        if ((n_cycle - curr_op_st) == duration.at(program[i].first)) {
            curr_op_st = n_cycle;
            if (program[i].first == "addx") {
                register_x += program[i].second;
            }
            ++i;
        }

        if (i == program.size()) {
            std::cout << std::endl;
            break;
        }
        
        if (std::abs(register_x - beam_pos) <= 1) {
            std::cout << "█";
        }
        else {
            std::cout << ' ';
        }

        beam_pos = (beam_pos + 1) % 40;

        if (beam_pos == 0)
            std::cout << std::endl << "\t\t";
    }
}
