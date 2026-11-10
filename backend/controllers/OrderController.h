#pragma once

#include <drogon/HttpController.h>

#include "filters/AuthFilter.h"

using namespace drogon;

class OrderController : public drogon::HttpController<OrderController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(OrderController::placeOrder, "/api/orders", Post, "AuthFilter");
    ADD_METHOD_TO(OrderController::getOrders, "/api/orders", Get, "AuthFilter");
    ADD_METHOD_TO(OrderController::getOrder, "/api/orders/{id}", Get, "AuthFilter");
    METHOD_LIST_END

    void placeOrder(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getOrders(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getOrder(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string id);
};
