// AOC-2022
// Day7-p1 
// 
// Date: Wednesday December 07, 2022
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

constexpr const std::string_view space{ " " };

struct fs_node {
    int64_t size;
    std::string name;

    std::vector<std::unique_ptr<fs_node>> childs;
};

void read_fs(fs_node *curr_node, std::stack<fs_node *> &st_helper);

int64_t update_sizes(fs_node *curr_node);

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    auto root = std::make_unique<fs_node>();
    root->name = "/";
    root->size = -1;

    std::stack<fs_node *> st_helper;

    st_helper.push(root.get());

    read_fs(root.get(), st_helper);
    update_sizes(root.get());

    std::queue<fs_node *> q;
    q.push(root.get());

    int64_t ans = 0;
    constexpr const int64_t MAX_SIZE = 100000;

    while (! q.empty()) {
        auto curr = q.front();
        q.pop();

        if (curr->childs.size() > 0) {
            if (curr->size <= MAX_SIZE) {
                ans += curr->size;
            }
        }

        for (auto &child : curr->childs) {
            q.push(child.get());
        }
    }

    std::cout << ans << std::endl;
}

void read_fs(fs_node *curr_node, std::stack<fs_node *> &st_helper) {
    std::string line;

    if (! std::getline(std::cin, line)) {
        return;
    }

    const auto tokens = line
        | rv::split(space)
        | rv::transform([](auto &&str) {
            return str | rng::to<std::string>();
        })
        | rng::to<std::vector>();

    if (tokens[0] == "$") { 
        if (tokens[1] == "cd") {
            if (tokens[2] == "/") {
                while (st_helper.size() > 1) {
                    st_helper.pop();
                }
                return read_fs(st_helper.top(), st_helper);
            }
            else if (tokens[2] == "..") {
                st_helper.pop();
                return read_fs(st_helper.top(), st_helper); 
            }
            else {
                for (auto &child : curr_node->childs) {
                    if (child->name == tokens[2]) {
                        st_helper.push(child.get());
                        return read_fs(child.get(), st_helper);
                    }
                }
            }
        }
    }
    else {
        auto new_node = std::make_unique<fs_node>();

        if (tokens[0] == "dir") {
            new_node->size = -1;
            new_node->name = tokens[1];
        }
        else {
            new_node->size = std::stoi(tokens[0]);
            new_node->name = tokens[1];
        }

        curr_node->childs.push_back(std::move(new_node));

    }
    
    read_fs(curr_node, st_helper);
}

int64_t update_sizes(fs_node *curr_node) {
    if (curr_node->size != -1) {
        return curr_node->size;
    }

    curr_node->size = 0;

    for (auto &child : curr_node->childs) {
        curr_node->size += update_sizes(child.get());
    }

    return curr_node->size;
}
