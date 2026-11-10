#include "MenuController.h"

#include "store/MenuStore.h"
#include "utils/JsonResponse.h"
#include "utils/Serialize.h"

void MenuController::getCategories(const HttpRequestPtr &req,
                                     std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto categories = MenuStore::instance().getCategories();
    callback(jsonresponse::ok(serialize::toJson(categories)));
}

void MenuController::getItems(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback)
{
    std::optional<std::string> categoryId;
    auto param = req->getParameter("categoryId");
    if (!param.empty())
        categoryId = param;

    auto items = MenuStore::instance().getItems(categoryId);
    callback(jsonresponse::ok(serialize::toJson(items)));
}

void MenuController::getItem(const HttpRequestPtr &req,
                               std::function<void(const HttpResponsePtr &)> &&callback,
                               std::string id)
{
    auto item = MenuStore::instance().getItem(id);
    if (!item)
    {
        callback(jsonresponse::error(k404NotFound, "menu item not found"));
        return;
    }
    callback(jsonresponse::ok(serialize::toJson(*item)));
}
