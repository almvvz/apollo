#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#include "models/User.h"

class UserStore
{
  public:
    static UserStore &instance();

    // Returns nullopt if the email is already registered.
    std::optional<User> createUser(const std::string &email,
                                    const std::string &displayName,
                                    const std::string &passwordHash,
                                    const std::string &passwordSalt);

    std::optional<User> findByEmail(const std::string &email) const;
    std::optional<User> findById(const std::string &userId) const;

  private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, User> usersById_;
    std::unordered_map<std::string, std::string> idByEmail_;
};
