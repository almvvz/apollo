#pragma once

#include <drogon/HttpResponse.h>
#include <json/json.h>

namespace jsonresponse
{
inline drogon::HttpResponsePtr ok(const Json::Value &body,
                                   drogon::HttpStatusCode status = drogon::k200OK)
{
    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
    resp->setStatusCode(status);
    return resp;
}

inline drogon::HttpResponsePtr error(drogon::HttpStatusCode status, const std::string &message)
{
    Json::Value body;
    body["error"] = message;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
    resp->setStatusCode(status);
    return resp;
}

inline drogon::HttpResponsePtr noContent()
{
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k204NoContent);
    return resp;
}
}  // namespace jsonresponse
