#include "AuthFilter.h"

#include "store/SessionStore.h"
#include "utils/JsonResponse.h"

namespace
{
constexpr std::string_view kBearerPrefix = "Bearer ";
}

void AuthFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb)
{
    const std::string &authHeader = req->getHeader("Authorization");
    if (authHeader.size() <= kBearerPrefix.size() ||
        authHeader.compare(0, kBearerPrefix.size(), kBearerPrefix) != 0)
    {
        fcb(jsonresponse::error(k401Unauthorized, "unauthorized"));
        return;
    }

    std::string token = authHeader.substr(kBearerPrefix.size());
    auto userId = SessionStore::instance().findUserId(token);
    if (!userId)
    {
        fcb(jsonresponse::error(k401Unauthorized, "unauthorized"));
        return;
    }

    req->attributes()->insert("userId", *userId);
    req->attributes()->insert("authToken", token);
    fccb();
}
