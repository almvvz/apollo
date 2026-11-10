#include "PasswordHash.h"

#include <openssl/crypto.h>
#include <openssl/evp.h>

#include <vector>

#include "IdGen.h"

namespace
{
constexpr int kIterations = 100000;
constexpr int kSaltBytes = 16;
constexpr int kHashBytes = 32;

std::string toHex(const unsigned char *data, size_t len)
{
    static const char *hexDigits = "0123456789abcdef";
    std::string out;
    out.reserve(len * 2);
    for (size_t i = 0; i < len; ++i)
    {
        out.push_back(hexDigits[(data[i] >> 4) & 0xF]);
        out.push_back(hexDigits[data[i] & 0xF]);
    }
    return out;
}

std::vector<unsigned char> fromHex(const std::string &hex)
{
    std::vector<unsigned char> out;
    out.reserve(hex.size() / 2);
    for (size_t i = 0; i + 1 < hex.size(); i += 2)
    {
        out.push_back(static_cast<unsigned char>(std::stoul(hex.substr(i, 2), nullptr, 16)));
    }
    return out;
}

std::vector<unsigned char> derive(const std::string &password, const std::vector<unsigned char> &salt)
{
    std::vector<unsigned char> out(kHashBytes);
    PKCS5_PBKDF2_HMAC(password.data(),
                       static_cast<int>(password.size()),
                       salt.data(),
                       static_cast<int>(salt.size()),
                       kIterations,
                       EVP_sha256(),
                       kHashBytes,
                       out.data());
    return out;
}
}  // namespace

namespace passwordhash
{
SaltedHash hashPassword(const std::string &password)
{
    std::string saltHex = idgen::randomHex(kSaltBytes);
    auto salt = fromHex(saltHex);
    auto hash = derive(password, salt);
    return {saltHex, toHex(hash.data(), hash.size())};
}

bool verifyPassword(const std::string &password, const std::string &saltHex, const std::string &hashHex)
{
    auto salt = fromHex(saltHex);
    auto expected = fromHex(hashHex);
    auto actual = derive(password, salt);
    if (actual.size() != expected.size())
        return false;
    return CRYPTO_memcmp(actual.data(), expected.data(), actual.size()) == 0;
}
}  // namespace passwordhash
