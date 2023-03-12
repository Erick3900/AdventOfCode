// AOC-2022
// Day7-p2 
// 
// Date: Wednesday December 07, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <limits>
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

int64_t calculate_free_required(fs_node *curr_node, const int64_t required);

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

    constexpr const int64_t FS_SIZE = 70000000;
    constexpr const int64_t DES_SIZE = 30000000;
    const int64_t REQ_SIZE = DES_SIZE - (FS_SIZE - root->size);

    std::cout << calculate_free_required(root.get(), REQ_SIZE) << std::endl;
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

int64_t calculate_free_required(fs_node *curr_node, const int64_t required) {
    int64_t best = std::numeric_limits<int64_t>::max();

    for (auto &child : curr_node->childs) {
        if (child->childs.size() > 0 && child->size > required) {
            best = std::min(best, calculate_free_required(child.get(), required));
        }
    }

    if (best == std::numeric_limits<int64_t>::max()) {
        return curr_node->size;
    }

    return best;
}
