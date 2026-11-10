#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MenuController : public drogon::HttpController<MenuController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MenuController::getCategories, "/api/menu/categories", Get);
    ADD_METHOD_TO(MenuController::getItems, "/api/menu/items", Get);
    ADD_METHOD_TO(MenuController::getItem, "/api/menu/items/{id}", Get);
    METHOD_LIST_END

    void getCategories(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback);
    void getItems(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getItem(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback,
                 std::string id);
};
