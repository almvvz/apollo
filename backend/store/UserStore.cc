#include "UserStore.h"

#include "utils/IdGen.h"

UserStore &UserStore::instance()
{
    static UserStore store;
    return store;
}

std::optional<User> UserStore::createUser(const std::string &email,
                                           const std::string &displayName,
                                           const std::string &passwordHash,
                                           const std::string &passwordSalt)
{
    std::lock_guard lock(mutex_);
    if (idByEmail_.count(email))
        return std::nullopt;

    User user;
    user.id = idgen::randomHex(16);
    user.email = email;
    user.displayName = displayName;
    user.passwordHash = passwordHash;
    user.passwordSalt = passwordSalt;
    user.createdAt = idgen::isoNow();

    idByEmail_[email] = user.id;
    usersById_[user.id] = user;
    return user;
}

std::optional<User> UserStore::findByEmail(const std::string &email) const
{
    std::lock_guard lock(mutex_);
    auto it = idByEmail_.find(email);
    if (it == idByEmail_.end())
        return std::nullopt;
    return usersById_.at(it->second);
}

std::optional<User> UserStore::findById(const std::string &userId) const
{
    std::lock_guard lock(mutex_);
    auto it = usersById_.find(userId);
    if (it == usersById_.end())
        return std::nullopt;
    return it->second;
}
