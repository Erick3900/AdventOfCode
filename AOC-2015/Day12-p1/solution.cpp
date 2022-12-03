// AOC-2015
// Day12-p1 
// 
// Date: Sunday November 27, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <nlohmann/json.hpp>

#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

namespace nlh = nlohmann;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss{ line };

    nlh::json json_input;

    ss >> json_input;

    std::function<void(const nlh::json &)> recurse_object;

    int64_t total_sum = 0;
        
    recurse_object = [&recurse_object, &total_sum](const nlh::json &jsonObject) {
        const auto object_trait = [&]() {
            for (const auto &[k, v] : jsonObject.items()) {
                recurse_object(v);
            }
        };

        const auto array_traits = [&]() {
            for (const auto &e : jsonObject) {
                recurse_object(e);
            }
        };

        if (jsonObject.is_object()) {
            return object_trait();
        }
        else if (jsonObject.is_array()) {
            return array_traits();
        }
        else if (jsonObject.is_number()) {
            total_sum += jsonObject.get<int64_t>();
        }
    };

    recurse_object(json_input);

    std::cout << total_sum << std::endl;
}
