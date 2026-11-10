#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

class SessionStore
{
  public:
    static SessionStore &instance();

    std::string createSession(const std::string &userId);
    std::optional<std::string> findUserId(const std::string &token) const;
    void destroySession(const std::string &token);

  private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::string> userIdByToken_;
};
