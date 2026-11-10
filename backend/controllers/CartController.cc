#include "CartController.h"

#include "store/CartStore.h"
#include "utils/JsonResponse.h"
#include "utils/Serialize.h"

namespace
{
std::vector<std::string> jsonToStringVector(const Json::Value &arr)
{
    std::vector<std::string> out;
    for (const auto &v : arr) out.push_back(v.asString());
    return out;
}
}  // namespace

void CartController::getCart(const HttpRequestPtr &req,
                               std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto userId = req->attributes()->get<std::string>("userId");
    callback(jsonresponse::ok(serialize::toJson(CartStore::instance().getCart(userId))));
}

void CartController::clearCart(const HttpRequestPtr &req,
                                 std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto userId = req->attributes()->get<std::string>("userId");
    callback(jsonresponse::ok(serialize::toJson(CartStore::instance().clearCart(userId))));
}

void CartController::addItem(const HttpRequestPtr &req,
                               std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto userId = req->attributes()->get<std::string>("userId");

    auto json = req->getJsonObject();
    if (!json)
    {
        callback(jsonresponse::error(k400BadRequest, "invalid JSON body"));
        return;
    }

    std::string menuItemId = (*json).get("menuItemId", "").asString();
    int quantity = (*json).get("quantity", 1).asInt();
    std::string selectedSizeId = (*json).get("selectedSizeId", "").asString();
    std::vector<std::string> selectedAddOnIds = jsonToStringVector((*json)["selectedAddOnIds"]);

    if (menuItemId.empty())
    {
        callback(jsonresponse::error(k400BadRequest, "menuItemId is required"));
        return;
    }

    auto result =
        CartStore::instance().addItem(userId, menuItemId, quantity, selectedSizeId, selectedAddOnIds);
    if (!result.ok)
    {
        callback(jsonresponse::error(k400BadRequest, result.error));
        return;
    }
    callback(jsonresponse::ok(serialize::toJson(result.cart), k201Created));
}

void CartController::updateItem(const HttpRequestPtr &req,
                                  std::function<void(const HttpResponsePtr &)> &&callback,
                                  std::string id)
{
    auto userId = req->attributes()->get<std::string>("userId");

    auto json = req->getJsonObject();
    if (!json)
    {
        callback(jsonresponse::error(k400BadRequest, "invalid JSON body"));
        return;
    }

    std::optional<int> quantity;
    if (json->isMember("quantity"))
        quantity = (*json)["quantity"].asInt();

    std::optional<std::string> selectedSizeId;
    if (json->isMember("selectedSizeId"))
        selectedSizeId = (*json)["selectedSizeId"].asString();

    std::optional<std::vector<std::string>> selectedAddOnIds;
    if (json->isMember("selectedAddOnIds"))
        selectedAddOnIds = jsonToStringVector((*json)["selectedAddOnIds"]);

    auto result =
        CartStore::instance().updateItem(userId, id, quantity, selectedSizeId, selectedAddOnIds);
    if (!result.ok)
    {
        callback(jsonresponse::error(
            result.error == "cart item not found" ? k404NotFound : k400BadRequest, result.error));
        return;
    }
    callback(jsonresponse::ok(serialize::toJson(result.cart)));
}

void CartController::removeItem(const HttpRequestPtr &req,
                                  std::function<void(const HttpResponsePtr &)> &&callback,
                                  std::string id)
{
    auto userId = req->attributes()->get<std::string>("userId");
    auto result = CartStore::instance().removeItem(userId, id);
    if (!result.ok)
    {
        callback(jsonresponse::error(k404NotFound, result.error));
        return;
    }
    callback(jsonresponse::ok(serialize::toJson(result.cart)));
}
