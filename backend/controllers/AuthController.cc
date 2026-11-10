#include "AuthController.h"

#include "store/SessionStore.h"
#include "store/UserStore.h"
#include "utils/JsonResponse.h"
#include "utils/PasswordHash.h"
#include "utils/Serialize.h"

namespace
{
bool isValidEmail(const std::string &email)
{
    auto at = email.find('@');
    return at != std::string::npos && at > 0 && at < email.size() - 1;
}
}  // namespace

void AuthController::signup(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json)
    {
        callback(jsonresponse::error(k400BadRequest, "invalid JSON body"));
        return;
    }

    std::string email = (*json).get("email", "").asString();
    std::string password = (*json).get("password", "").asString();
    std::string displayName = (*json).get("displayName", "").asString();

    if (!isValidEmail(email) || password.size() < 8 || displayName.empty())
    {
        callback(jsonresponse::error(
            k400BadRequest, "email, displayName, and password (min 8 chars) are required"));
        return;
    }

    auto hashed = passwordhash::hashPassword(password);
    auto user = UserStore::instance().createUser(email, displayName, hashed.hashHex, hashed.saltHex);
    if (!user)
    {
        callback(jsonresponse::error(k409Conflict, "an account with this email already exists"));
        return;
    }

    std::string token = SessionStore::instance().createSession(user->id);

    Json::Value body;
    body["user"] = serialize::toJson(*user);
    body["token"] = token;
    callback(jsonresponse::ok(body, k201Created));
}

void AuthController::login(const HttpRequestPtr &req,
                             std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json)
    {
        callback(jsonresponse::error(k400BadRequest, "invalid JSON body"));
        return;
    }

    std::string email = (*json).get("email", "").asString();
    std::string password = (*json).get("password", "").asString();

    auto user = UserStore::instance().findByEmail(email);
    if (!user || !passwordhash::verifyPassword(password, user->passwordSalt, user->passwordHash))
    {
        callback(jsonresponse::error(k401Unauthorized, "invalid email or password"));
        return;
    }

    std::string token = SessionStore::instance().createSession(user->id);

    Json::Value body;
    body["user"] = serialize::toJson(*user);
    body["token"] = token;
    callback(jsonresponse::ok(body));
}

void AuthController::logout(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto token = req->attributes()->get<std::string>("authToken");
    SessionStore::instance().destroySession(token);
    callback(jsonresponse::noContent());
}

void AuthController::me(const HttpRequestPtr &req,
                          std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto userId = req->attributes()->get<std::string>("userId");
    auto user = UserStore::instance().findById(userId);
    if (!user)
    {
        callback(jsonresponse::error(k401Unauthorized, "unauthorized"));
        return;
    }
    callback(jsonresponse::ok(serialize::toJson(*user)));
}
