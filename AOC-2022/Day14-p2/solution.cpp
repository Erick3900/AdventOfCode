// AOC-2022
// Day14-p2 
// 
// Date: Wednesday December 14, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>
#include <fmt/format.h>
#include <fmt/chrono.h>

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

using row_t = std::vector<char>;
using matrix_t = std::vector<row_t>;

matrix_t parseInput(std::istream &in);

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto grid = parseInput(std::cin);

    int stx = 500;
    int sty = 0;

    int rocksCount = 0;

    auto valid = [&](int x, int y) {
        return (
            x >= 0 &&
            y >= 0 &&
            x <  grid[0].size() && 
            y <  grid.size()
        );
    };

    auto showGrid = [&]() {
        for (auto &row : grid) {
            for (int i = 0; i < row.size(); ++i) {
                std::cout << row[i];
            }
            std::cout << std::endl;
        }
    };

    do {
        int cx = stx;
        int cy = sty;

        bool moved = true;

        do {
            moved = true;

            if (valid(cx, cy + 1) && grid[cy + 1][cx] == '.') {
                cy += 1;
            }
            else if (valid(cx - 1, cy + 1) && grid[cy + 1][cx - 1] == '.') {
                cx -= 1;
                cy += 1;
            }
            else if (valid(cx + 1, cy + 1) && grid[cy + 1][cx + 1] == '.') {
                cx += 1;
                cy += 1;
            }
            else {
                moved = false;
                if (! valid(cx, cy + 1)) {
                    cy++;
                }
            }
        } while (moved);

        if (! valid(cx, cy) || grid[cy][cx] != '.') {
            break;
        }
        else {
            rocksCount++;
            grid[cy][cx] = '*';
        }
    } while (true);

    std::cout << rocksCount << std::endl;
}

matrix_t parseInput(std::istream &in) {
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();

    auto parsedLines = rng::getlines(in)
        | rv::transform([&](const std::string &line) {
            std::regex coordsRgx{
                 "(\\d+,\\d+)( -> )?",
                 std::regex_constants::ECMAScript |
                 std::regex_constants::multiline
            };
            
            auto it = std::regex_iterator(line.begin(), line.end(), coordsRgx);
            auto it_end = std::sregex_iterator{};
            
            std::smatch matchVar;

            std::vector<std::pair<int, int>> coordsList;

            coordsList.reserve(std::distance(it, it_end));

            for (auto i = it; i != it_end; ++i) {
                matchVar = *i;

                auto [x, y] = [](std::string coords){
                    auto vec = coords
                        | rv::split(std::string_view{ "," })
                        | rv::transform([](auto &&c) {
                            return std::stoi(c | rng::to<std::string>());
                        })
                        | rng::to<std::vector>();

                    return std::pair{ vec[0], vec[1] };
                }(matchVar.str(1));

                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);

                coordsList.push_back({ x, y });
            }

            return coordsList;
        })
        | rng::to<std::vector>();

    // NOT PROUD OF THIS SOLUTION BUT IT WORKS!
    matrix_t mat( maxY + 3, row_t( (maxX + 1) * 2, '.' ) );

    for (auto &rocks : parsedLines) {
        for (int i = 1; i < rocks.size(); ++i) {
            auto [cx, cy] = rocks[i - 1];
            auto [nx, ny] = rocks[i];
            auto [dx, dy] = std::pair{ nx - cx, ny - cy };

            dx = dx != 0 ? std::signbit(dx) ? -1 : 1 : 0;
            dy = dy != 0 ? std::signbit(dy) ? -1 : 1 : 0;

            while (cx != nx || cy != ny) {
                mat[cy][cx] = '#';
                cx += dx;
                cy += dy;
            }
            mat[ny][nx] = '#';
        }
    }
    
    for (auto &cell : mat.back())
        cell = '#';

    return mat;
}
