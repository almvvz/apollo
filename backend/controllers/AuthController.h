#pragma once

#include <drogon/HttpController.h>

#include "filters/AuthFilter.h"

using namespace drogon;

class AuthController : public drogon::HttpController<AuthController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AuthController::signup, "/api/auth/signup", Post);
    ADD_METHOD_TO(AuthController::login, "/api/auth/login", Post);
    ADD_METHOD_TO(AuthController::logout, "/api/auth/logout", Post, "AuthFilter");
    ADD_METHOD_TO(AuthController::me, "/api/auth/me", Get, "AuthFilter");
    METHOD_LIST_END

    void signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void me(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
