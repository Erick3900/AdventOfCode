// AOC-2015
// Day4-p1 
// 
// Date: Saturday November 26, 2022
//
// Author: Erick Saúl
// Github: @Erick3900
// Twitter: @Erick_Alcachofa

#include <bits/stdc++.h>

#include <fmt/format.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/cryptlib.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

#ifdef _DEBUG
#    define deb(x) std::clog << #x << " = " << x << std::endl;
#    define deb2(x, y) std::clog << #x << " = " << x << "\t|\t" << #y << " = " << y << std::endl;
#    define debug(x) { (x) };
#else
#    define deb(x)
#    define deb2(x)
#    define debug(x)
#endif

namespace crypto = CryptoPP;

int main(int argc, char *argv[]) {
    // std::ios_base::sync_with_stdio(false), 
    //     std::cin.tie(nullptr), 
    //     std::cout.tie(nullptr);

    std::stringstream ss;

    crypto::HexEncoder encoder{ new crypto::FileSink(ss) };

    constexpr std::string_view base{ "yzbqklnj" };
    
    int64_t iter = 0;

    while (true) {
        std::string message = fmt::format("{}{}", base, ++iter);
        std::string digest;

        crypto::Weak::MD5 hash;

        hash.Update((const crypto::byte *) &message[0], message.size());
        
        digest.resize(hash.DigestSize());

        hash.Final((crypto::byte *) &digest[0]);

        crypto::StringSource(digest, true, new crypto::Redirector{ encoder });

        int zero_count = 0;
        const std::string hash_result = ss.str();
        ss = std::stringstream{};
        
        while (hash_result[zero_count] == '0') {
            ++zero_count;

            if (zero_count == 5) {
                std::cout << iter << std::endl;
                return 0;
            }
        }

        if ((iter % 1000) == 0) {
            std::cout << iter << std::endl;
        }
    }
}
