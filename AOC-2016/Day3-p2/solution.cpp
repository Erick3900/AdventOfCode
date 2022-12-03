// AOC-2016
// Day3-p2 
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
namespace rv = ranges::views;

template <typename T>
class GetType;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto ans = rng::istream_view<int>(std::cin)
      | rv::chunk(3)
      | rv::chunk(3)
      | rv::transform([](auto &&e) {
            const auto vec_vec = e
            | rv::transform([](auto &&o) {
                  return o | rng::to<std::vector>();
              })
            | rng::to<std::vector>();
            
            return rng::zip_view(vec_vec[0], vec_vec[1], vec_vec[2]) | rng::to<std::vector>();
        })
    | rv::join
    | rv::transform([](auto &&e) {
          const auto [l1, l2, l3] = e;
          return ((l1 + l2) > l3) && ((l2 + l3) > l1) && ((l1 + l3) > l2);
      })
    | rng::to<std::vector>();

    std::cout << rng::accumulate(ans, 0) << std::endl;
}
