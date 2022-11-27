// AOC-2015
// Day3-p1 
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

struct coord {
    int16_t x;
    int16_t y;

    void move_up() {
        this->y -= 1;
    }

    void move_down() {
        this->y += 1;
    }

    void move_left() {
        this->x -= 1;
    }

    void move_right() {
        this->x += 1;
    }

    bool operator==(const coord &other) const {
        return this->x == other.x && this->y == other.y;
    }
};

template <>
struct std::hash<coord> {
    size_t operator()(const coord &c) const {
        return std::hash<uint64_t>{}((static_cast<uint64_t>(c.x) << 32) | static_cast<uint64_t>(c.y));
    }
};

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::string moves;

    std::getline(std::cin, moves);

    coord santa_position{ 0, 0 };
    coord robosanta_position{ 0, 0 };
    std::unordered_set<coord> unique_coords;

    for (const auto &dir : moves) {
        switch(dir) {
            case '^':
                santa_position.move_up();
                break;
            case 'v':
                santa_position.move_down();
                break;
            case '>':
                santa_position.move_right();
                break;
            case '<':
                santa_position.move_left();
                break;
            default: 
                break;
        }

        unique_coords.insert(santa_position);
    }

    std::cout << unique_coords.size() << std::endl;
}