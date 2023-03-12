// AOC-2022
// Day9-p1 
// 
// Date: Friday December 09, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <fmt/format.h>

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

enum class Direction {
    Up, Left, Right, Down
};

struct Coord {
    int x;
    int y;

    void move(Direction dir) {
        switch (dir) {
            case Direction::Up:
                y -= 1;
                break;
            case Direction::Down:
                y += 1;
                break;
            case Direction::Left:
                x -= 1;
                break;
            case Direction::Right:
                x += 1;
                break;
        }
    }

    bool operator==(const Coord &other) const {
        return x == other.x && y == other.y; 
    }
};

template <>
struct std::hash<Coord> {
    std::size_t operator()(const Coord &c) const {
        const int64_t id = static_cast<int64_t>(c.x) << 32 | static_cast<int64_t>(c.y);

        return std::hash<int64_t>{}(id);
    }
};

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::string direction;
    int amount;

    Coord headPosition{ 0, 0 };
    Coord tailPosition{ 0, 0 };

    std::unordered_set<Coord> uniques;

    uniques.insert(tailPosition);

    while (std::cin >> direction >> amount) {
        for (int i = 0; i < amount; ++i) {
            switch (direction[0]) {
                case 'D': headPosition.move(Direction::Down);   break;
                case 'U': headPosition.move(Direction::Up);     break;
                case 'L': headPosition.move(Direction::Left);   break;
                case 'R': headPosition.move(Direction::Right);  break;
            }

            const auto dist = std::max(
                std::abs(headPosition.x - tailPosition.x), 
                std::abs(headPosition.y - tailPosition.y)
            );

            if (dist >= 2) {
                if (headPosition.x == tailPosition.x) {
                    tailPosition.y += ((headPosition.y - tailPosition.y) < 0 ? -1 : 1);
                }
                else if (headPosition.y == tailPosition.y) {
                    tailPosition.x += ((headPosition.x - tailPosition.x) < 0 ? -1 : 1);
                }
                else {
                    tailPosition.x += ((headPosition.x - tailPosition.x) < 0 ? -1 : 1);
                    tailPosition.y += ((headPosition.y - tailPosition.y) < 0 ? -1 : 1);
                }
            }

            uniques.insert(tailPosition);
        }
    }

    std::cout << uniques.size() << std::endl;
}
