#pragma once

#include <drogon/HttpFilter.h>

using namespace drogon;

// Requires a valid "Authorization: Bearer <token>" header. On success,
// stashes the resolved userId into req->attributes() under the key
// "userId" for downstream controllers to read.
class AuthFilter : public drogon::HttpFilter<AuthFilter>
{
  public:
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};
