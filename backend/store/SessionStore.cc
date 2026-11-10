#include "SessionStore.h"

#include "utils/IdGen.h"

SessionStore &SessionStore::instance()
{
    static SessionStore store;
    return store;
}

std::string SessionStore::createSession(const std::string &userId)
{
    std::string token = idgen::randomHex(32);
    std::lock_guard lock(mutex_);
    userIdByToken_[token] = userId;
    return token;
}

std::optional<std::string> SessionStore::findUserId(const std::string &token) const
{
    std::lock_guard lock(mutex_);
    auto it = userIdByToken_.find(token);
    if (it == userIdByToken_.end())
        return std::nullopt;
    return it->second;
}

void SessionStore::destroySession(const std::string &token)
{
    std::lock_guard lock(mutex_);
    userIdByToken_.erase(token);
}
