// AOC-2022
// Day11-p2 
// 
// Date: Sunday December 11, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>
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

namespace rng = ranges;
namespace rv = rng::views;

template <typename T>
struct GetType;

// SPOILER FROM REDDIT
// constexpr const int64_t MOD{ 9699690 };

struct Monkey {
    int monkeyId;

    int64_t modValue;

    size_t trueMonkeyId;
    size_t falseMonkeyId;

    std::vector<int64_t> items;
    std::vector<std::string> opTokens;
};

std::vector<Monkey> parseInput();
std::vector<std::string> toPostfix(const std::vector<std::string> &ops);
int64_t gcdExtended(int64_t a, int64_t b, int64_t *x, int64_t *y);
int64_t modInverse(int64_t b, int64_t m);
int64_t modDivide(int64_t a, int64_t b, int64_t m);


int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    std::vector<Monkey> monkeys = parseInput();

    // The idea of how to get the modulus number was from reddit
    // TODO: Generate the primes so the solution would work for any input
    auto getMOD = [](int64_t maxPrime){
        const std::vector<int64_t> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
        const auto maxPrimePos = [&primes, &maxPrime](){
            auto it = std::upper_bound(primes.begin(), primes.end(), maxPrime);

            if (it == primes.end()) {
                throw std::runtime_error("PANIC");
            }
            
            return it - primes.begin();
        }();

        int iter = 1;
        bool condition = false;

        while (! condition) {
            condition = true;

            for (int i = 0; i < maxPrimePos; ++i) {
                condition = condition && ((iter % primes[i]) == 0);
            }

            iter++;
        }

        return iter - 1;
    };

    int64_t maxPrime = -1;

    for (auto &monkey : monkeys) {
        maxPrime = std::max(maxPrime, monkey.modValue);
    }

    const int64_t MOD = getMOD(maxPrime);

    constexpr const int N_Rounds = 10000;

    auto evaluateOperation = [&MOD](const std::vector<std::string> &ops, int64_t item) {
        std::stack<int64_t> operands;

        for (auto &op : ops) {
            if (op == "old") {
                operands.push(item);
            }
            else if (op == "+") {
                auto first_op = operands.top();  operands.pop();
                auto second_op = operands.top(); operands.pop();

                operands.push((second_op + first_op) % MOD);
            }
            else if (op == "-") {
                auto first_op = operands.top();  operands.pop();
                auto second_op = operands.top(); operands.pop();

                operands.push((second_op - first_op) % MOD);
            }
            else if (op == "*") {
                auto first_op = operands.top();  operands.pop();
                auto second_op = operands.top(); operands.pop();

                operands.push((second_op * first_op) % MOD);
            }
            else if (op == "/") {
                auto first_op = operands.top();  operands.pop();
                auto second_op = operands.top(); operands.pop();

                operands.push((second_op / first_op) % MOD);
            }
            else {
                operands.push(std::stoll(op));
            }
        }

        return operands.top();
    };

    std::unordered_map<int, int64_t> inspections;

    for (int i = 0; i < N_Rounds; ++i) {
        for (auto &monkey : monkeys) {
            for (auto &item : monkey.items) {
                inspections[monkey.monkeyId]++;

                auto new_value = evaluateOperation(monkey.opTokens, item);

                if ((new_value % monkey.modValue) == 0) {
                    monkeys[monkey.trueMonkeyId].items.push_back(new_value);
                }
                else {
                    monkeys[monkey.falseMonkeyId].items.push_back(new_value);
                }
            }

            monkey.items.clear();
        }
    }

    auto data_sorted = inspections 
        | rv::transform([](auto &&d) {
            return std::pair<int, int64_t>{ d.first, d.second };
        })
        | rng::to<std::vector>();

    rng::sort(
        data_sorted,
        [](const auto &lhs, const auto &rhs) {
            return lhs.second > rhs.second;
        }
    );

    const int64_t monkeyBusiness = data_sorted[0].second * data_sorted[1].second;

    std::cout << monkeyBusiness << std::endl;
}

std::vector<Monkey> parseInput() {
    const std::string EmptyLine{ "" };
    constexpr std::string_view Sep{ ", " };
    constexpr std::string_view Space{ " " };

    auto input = rng::getlines_view(std::cin)
        | rv::split(EmptyLine)
        | rv::transform([&Sep, &Space](auto &&r) {
            const auto monkey_data = r | rng::to<std::vector>();
            const std::string monkey_items = monkey_data[1].substr(18, monkey_data[1].length() - 16);
            const std::string monkey_new_op_tokens = monkey_data[2].substr(19, monkey_data[2].length() - 17);

            Monkey m;

            m.monkeyId = std::stoi(monkey_data[0].substr(7, monkey_data[0].length() - 8));
            m.items = rng::split_view(monkey_items, Sep)
                | rv::transform([](auto &&item) {
                    return std::stol(item | rng::to<std::string>());
                })
                | rng::to<std::vector>();
            m.opTokens = toPostfix(
                rng::split_view(monkey_new_op_tokens, Space)
                    | rv::transform([](auto &&str) {
                        return str | rng::to<std::string>();
                    })
                    | rng::to<std::vector>()
            );
            m.modValue = std::stol(monkey_data[3].substr(21));
            m.trueMonkeyId = std::stoi(monkey_data[4].substr(29));
            m.falseMonkeyId = std::stoi(monkey_data[5].substr(30));

            return m;
        })
        | rng::to<std::vector>()
    ;

    return input;
}

std::vector<std::string> toPostfix(const std::vector<std::string> &ops) {
    std::vector<std::string> postfix;
    postfix.reserve(ops.size());

    std::stack<std::string> helper;

    auto precedence = [](std::string_view op) {
        if (op == "/" || op == "*") {
            return 2;
        }
        
        if (op == "+" || op == "-") {
            return 1;
        }
        
        return -1;
    };

    auto isOperand = [](const std::string &token) {
        static const std::regex NumberRegex {
            "^-?[0-9]+$",
            std::regex_constants::ECMAScript |
            std::regex_constants::multiline 
        };
        
        std::smatch match;

        return token == "old" || std::regex_match(token, match, NumberRegex);
    };

    for (const auto &token : ops) {
        if (isOperand(token)) {
            postfix.push_back(token);
        }
        else {
            while (! helper.empty() && precedence(token) <= precedence(helper.top())) {
                postfix.push_back(helper.top());
                helper.pop();
            }
            helper.push(token);
        }
    }

    while (! helper.empty()) {
        postfix.push_back(helper.top());
        helper.pop();
    }

    return postfix;
}

