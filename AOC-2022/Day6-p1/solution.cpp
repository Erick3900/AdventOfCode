// AOC-2022
// Day6-p1 
// 
// Date: Tuesday December 06, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

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

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::string input;

    std::getline(std::cin, input);

    for (int i = 4; i < input.length(); ++i) {
        std::unordered_map<char, int> count;
        bool uniques = true;;

        for (int j = i - 4; j < i; ++j) {
            if (++count[input[j]] > 1) {
                uniques = false;
            }
        }

        if (uniques) {
            std::cout << (i) << std::endl;
            return 0;
        }
    }
}
