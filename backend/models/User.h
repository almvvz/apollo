#pragma once

#include <string>

struct User
{
    std::string id;
    std::string email;
    std::string displayName;
    std::string passwordHash;  // hex-encoded PBKDF2 output
    std::string passwordSalt;  // hex-encoded random salt
    std::string createdAt;     // ISO-8601
};
