// AOC-2022
// Day9-p2 
// 
// Date: Friday December 09, 2022
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

    Coord head{ 0, 0 };
    std::vector<Coord> rope;

    for (int i = 0; i < 9; ++i) {
        rope.push_back(Coord{ 0, 0 });
    }

    std::unordered_set<Coord> uniques;

    uniques.insert(rope[8]);

    const auto updateKnot = [](const Coord &head, Coord &tail) {
         const auto dist = std::max(
            std::abs(head.x - tail.x), 
            std::abs(head.y - tail.y)
        );

        if (dist >= 2) {
            if (head.x == tail.x) {
                tail.y += ((head.y - tail.y) < 0 ? -1 : 1);
            }
            else if (head.y == tail.y) {
                tail.x += ((head.x - tail.x) < 0 ? -1 : 1);
            }
            else {
                tail.x += ((head.x - tail.x) < 0 ? -1 : 1);
                tail.y += ((head.y - tail.y) < 0 ? -1 : 1);
            }
        } 
    };

    while (std::cin >> direction >> amount) {
        for (int i = 0; i < amount; ++i) {
            switch (direction[0]) {
                case 'D': head.move(Direction::Down);   break;
                case 'U': head.move(Direction::Up);     break;
                case 'L': head.move(Direction::Left);   break;
                case 'R': head.move(Direction::Right);  break;
            }

            updateKnot(head, rope[0]);

            for (int i = 1; i < 9; ++i) {
                updateKnot(rope[i - 1], rope[i]);
            }

            uniques.insert(rope[8]);
        }
    }

    std::cout << uniques.size() << std::endl;
}
