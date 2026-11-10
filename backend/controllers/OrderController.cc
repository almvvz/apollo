#include "OrderController.h"

#include "store/OrderStore.h"
#include "utils/JsonResponse.h"
#include "utils/Serialize.h"

void OrderController::placeOrder(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto userId = req->attributes()->get<std::string>("userId");
    auto result = OrderStore::instance().placeOrder(userId);
    if (!result.ok)
    {
        callback(jsonresponse::error(k400BadRequest, result.error));
        return;
    }

    Json::Value body;
    body["order"] = serialize::toJson(result.order);
    callback(jsonresponse::ok(body, k201Created));
}

void OrderController::getOrders(const HttpRequestPtr &req,
                                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto userId = req->attributes()->get<std::string>("userId");
    auto orders = OrderStore::instance().getOrders(userId);

    Json::Value body;
    body["orders"] = serialize::toJson(orders);
    callback(jsonresponse::ok(body));
}

void OrderController::getOrder(const HttpRequestPtr &req,
                                 std::function<void(const HttpResponsePtr &)> &&callback,
                                 std::string id)
{
    auto userId = req->attributes()->get<std::string>("userId");
    auto order = OrderStore::instance().getOrder(userId, id);
    if (!order)
    {
        callback(jsonresponse::error(k404NotFound, "order not found"));
        return;
    }

    Json::Value body;
    body["order"] = serialize::toJson(*order);
    callback(jsonresponse::ok(body));
}
