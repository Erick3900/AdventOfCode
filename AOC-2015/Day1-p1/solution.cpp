// AOC-2015
// Day1-p1 
// 
// Date: Saturday November 26, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::string line;

    std::getline(std::cin, line);

    int64_t current_floor = 0;

    for (auto &c : line) {
        switch(c) {
            case '(':
                ++current_floor;
                break;
            case ')':
                --current_floor;
                break;
        }
    }

    std::cout << current_floor << std::endl;
}
