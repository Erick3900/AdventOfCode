// AOC-2022
// Day12-p1
// 
// Date: Sunday December 12, 2022
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
class GetType;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto input = rng::getlines_view(std::cin)
        | rng::to<std::vector>();

    std::pair<int, int> orig;
    std::pair<int, int> dest;

    for (int y = 0; y < input.size(); ++y) {
        for (int x = 0; x < input[y].length(); ++x) {
            if (input[y][x] == 'E') {
                dest = { x, y };
            }
            else if (input[y][x] == 'S') {
                orig = { x, y };
            }
            else {

            }
        }
    }

    constexpr const int64_t INF{ std::numeric_limits<int64_t>::max() };

    auto valid = [&input](int x, int y) {
        return (
            x >= 0 && 
            y >= 0 &&
            x < input[0].length() &&
            y < input.size()
        );
    };

    auto reachable = [&](int f_x, int f_y, int t_x, int t_y) {
        if (f_x == dest.first && f_y == dest.second) {
            return input[t_y][t_x] == 'z';
        }
        
        if (t_x == orig.first && t_y == orig.second) {
            return input[f_y][f_x] == 'a';
        } 

        const auto height_diff = (input[f_y][f_x] - input[t_y][t_x]);

        return (
            height_diff <= 1
        );
    };

    std::vector<std::vector<bool>> visited{ 
        input.size(),
        std::vector<bool>(input[0].size(), false)
    };

    std::vector<std::vector<int64_t>> dist{ 
        input.size(),
        std::vector<int64_t>(input[0].size(), INF)
    };
    
    std::vector<std::vector<std::pair<int, int>>> path{ 
        input.size(),
        std::vector<std::pair<int, int>>(input[0].size(), { -1, -1 })
    };

    dist[dest.second][dest.first] = 0;

    for (int iy = 0; iy < input.size(); ++iy) {
        for (int ix = 0; ix < input[iy].size(); ++ix) {
            int vx = -1;
            int vy = -1;

            for (int jy = 0; jy < input.size(); ++jy) {
                for (int jx = 0; jx < input[jy].size(); ++jx) {
                    if (! visited[jy][jx] && (vx == -1 || (dist[jy][jx] < dist[vy][vx]))) {
                        vx = jx;
                        vy = jy;
                    }
                }
            }

            if (dist[vy][vx] == INF) {
                break;
            }

            visited[vy][vx] = true;

            auto visitNeighbor = std::bind_front([&valid, &reachable, &dist, &path](int x, int y, int off_x, int off_y) {
                const auto d_x = x + off_x;
                const auto d_y = y + off_y;

                if (valid(d_x, d_y)) {
                    if (reachable(x, y, d_x, d_y)) {
                        if ((dist[y][x] + 1) < dist[d_y][d_x]) {
                            dist[d_y][d_x] = dist[y][x] + 1;
                            path[d_y][d_x] = { x, y };
                        }
                    }
                }
            }, vx, vy);

            visitNeighbor(  1,  0);
            visitNeighbor( -1,  0);
            visitNeighbor(  0,  1);
            visitNeighbor(  0, -1);
        }
    }    std::cout << dist[orig.second][orig.first] << std::endl;
}
