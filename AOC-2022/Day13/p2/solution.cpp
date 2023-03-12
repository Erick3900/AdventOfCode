// AOC-2022
// Day13-p2 
// 
// Date: Tuesday December 13, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa
// Mastodon: @alcachofa@social.linux.pizza

#include <bits/stdc++.h>

#include <range/v3/all.hpp>

#include <fmt/ostream.h>
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

struct packet {
    std::variant<int, std::vector<packet>> value;
    bool flag = false;

    const std::vector<packet> &asList() const {
        return std::get<std::vector<packet>>(value);
    }

    const int &asInt() const {
        return std::get<int>(value);
    }

    std::vector<packet> &asList() {
        return std::get<std::vector<packet>>(value);
    }

    int &asInt() {
        return std::get<int>(value);
    }

    bool isList() const {
        return ! std::holds_alternative<int>(value);
    }

    std::string toString() const {
        if (! isList()) {
            return fmt::to_string(asInt());
        }
        else {
            return fmt::format("[{}]", 
                fmt::join(
                    asList()
                        | rv::transform([](const packet &packet) {
                            return packet.toString();
                        }),
                    ", "
                )
            );
        }
    }

    std::ostream &operator<<(std::ostream &os) {
        return os << toString();
    }
};

std::strong_ordering operator<=>(const packet &lhs, const packet &rhs) {
    if (lhs.isList() && rhs.isList()) {
        const auto &l_list = lhs.asList();
        const auto &r_list = rhs.asList();

        size_t sz = std::min(l_list.size(), r_list.size());
        
        for (size_t i = 0; i < sz; ++i) {
            auto comp = l_list[i] <=> r_list[i];

            if (comp == std::strong_ordering::less) {
                return std::strong_ordering::less;
            }
            else if (comp == std::strong_ordering::greater) {
                return std::strong_ordering::greater;
            } 
        }

        if (l_list.size() != r_list.size()) {
            return l_list.size() <=> r_list.size();
        }

        return std::strong_ordering::equal;
    }
    else if (lhs.isList() && !rhs.isList()) {
        return lhs <=> packet{ std::vector<packet>{ rhs } };
    }
    else if (!lhs.isList() && rhs.isList()) {
        return packet{ std::vector<packet>{ lhs } } <=> rhs;
    }

    return lhs.asInt() <=> rhs.asInt();
}

using chunk_t = std::tuple<packet, packet>;

std::vector<packet> parseInput(std::istream &in);
packet toPacket(const std::vector<std::string> &data);

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false), 
        std::cin.tie(nullptr), 
        std::cout.tie(nullptr);

    int ans = 1;

    std::vector<packet> packets = parseInput(std::cin);

    packets.push_back({ std::vector{ packet{ std::vector{ packet{ 2 } } } }, true });
    packets.push_back({ std::vector{ packet{ std::vector{ packet{ 6 } } } }, true });

    std::sort(packets.begin(), packets.end());

    for (int i = 0; i < packets.size(); ++i) {
        if (packets[i].flag) {
            ans *= (i + 1);
        }
    }

    std::cout << ans << std::endl;
}

std::vector<packet> parseInput(std::istream &in) {
    const std::string EmptyString{ "" };
    constexpr const std::string_view Comma{ "," };
    constexpr const std::string_view LBracket{ "[" };
    constexpr const std::string_view RBracket{ "]" };

    auto parsedInput = rng::getlines(std::cin)
        | rv::filter([&](auto &&str) {
            return str != EmptyString;
        })
        | rv::transform([&](auto &&el) {
            auto splitted = el
                | rv::split(Comma)
                | rv::transform([](auto &&el) {
                    return el | rng::to<std::string>();
                })
                | rng::to<std::vector>()
            ;
            std::regex matchBrackets {
                "\\[|\\]",
                std::regex_constants::ECMAScript |
                std::regex_constants::multiline
            };

            std::vector<std::string> tokens;

            for (const auto &e : splitted) {
                std::smatch matchVar;

                auto it = std::regex_iterator(e.begin(), e.end(), matchBrackets);
                auto it_end = std::sregex_iterator{};

                if (std::distance(it, it_end)) {
                    for (auto i = it; it != it_end; ++it) {
                        matchVar = *it;

                        auto prefix = matchVar.prefix().str();
                        
                        if (! prefix.empty()) {
                            tokens.push_back(prefix);
                        }

                        tokens.push_back(matchVar.str());
                    }

                    auto suffix = matchVar.suffix().str();

                    if (! suffix.empty()) {
                        tokens.push_back(suffix);
                    }
                }
                else {
                    tokens.push_back(e);
                }
            }

            return toPacket(tokens);
        })
        | rng::to<std::vector>();
    ;

    return parsedInput;
}

packet toPacket(const std::vector<std::string> &data) {
    std::stack<packet> p;

    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == "[") {
            p.push({ std::vector<packet>{} });
        }
        else if (data[i] == "]") {
            if (p.size() > 1) {
                auto top = p.top(); p.pop();
                p.top().asList().push_back(std::move(top));
            }
        }
        else {
            p.top().asList().push_back({ std::stoi(data[i]) });
        }
    }

    return p.top();
}
