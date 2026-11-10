#include "HealthController.h"

#include <chrono>

#include "utils/IdGen.h"
#include "utils/JsonResponse.h"

namespace
{
const auto kStartTime = std::chrono::steady_clock::now();
}

void HealthController::health(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto uptime = std::chrono::duration_cast<std::chrono::seconds>(
                      std::chrono::steady_clock::now() - kStartTime)
                      .count();

    Json::Value body;
    body["status"] = "ok";
    body["uptimeSeconds"] = static_cast<Json::Int64>(uptime);
    body["timestamp"] = idgen::isoNow();
    callback(jsonresponse::ok(body));
}
