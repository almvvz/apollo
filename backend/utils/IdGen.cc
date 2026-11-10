#include "IdGen.h"

#include <openssl/rand.h>

#include <chrono>
#include <cstdio>
#include <ctime>
#include <vector>

namespace idgen
{
std::string randomHex(size_t numBytes)
{
    std::vector<unsigned char> buf(numBytes);
    RAND_bytes(buf.data(), static_cast<int>(numBytes));

    static const char *hexDigits = "0123456789abcdef";
    std::string out;
    out.reserve(numBytes * 2);
    for (unsigned char byte : buf)
    {
        out.push_back(hexDigits[(byte >> 4) & 0xF]);
        out.push_back(hexDigits[byte & 0xF]);
    }
    return out;
}

std::string isoNow()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tmUtc{};
    gmtime_r(&t, &tmUtc);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tmUtc);
    return std::string(buf);
}
}  // namespace idgen
