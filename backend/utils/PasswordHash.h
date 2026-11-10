#pragma once

#include <string>

// Demo-grade password hashing (PBKDF2-HMAC-SHA256). Not a substitute for
// bcrypt/argon2 in a real production system, but adequate for this
// no-database learning project.
namespace passwordhash
{
struct SaltedHash
{
    std::string saltHex;
    std::string hashHex;
};

SaltedHash hashPassword(const std::string &password);
bool verifyPassword(const std::string &password, const std::string &saltHex, const std::string &hashHex);
}  // namespace passwordhash
