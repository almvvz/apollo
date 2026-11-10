#pragma once

#include <drogon/HttpController.h>

#include "filters/AuthFilter.h"

using namespace drogon;

class CartController : public drogon::HttpController<CartController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CartController::getCart, "/api/cart", Get, "AuthFilter");
    ADD_METHOD_TO(CartController::clearCart, "/api/cart", Delete, "AuthFilter");
    ADD_METHOD_TO(CartController::addItem, "/api/cart/items", Post, "AuthFilter");
    ADD_METHOD_TO(CartController::updateItem, "/api/cart/items/{id}", Patch, "AuthFilter");
    ADD_METHOD_TO(CartController::removeItem, "/api/cart/items/{id}", Delete, "AuthFilter");
    METHOD_LIST_END

    void getCart(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void clearCart(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void addItem(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateItem(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string id);
    void removeItem(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string id);
};
