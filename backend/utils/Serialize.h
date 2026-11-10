#pragma once

#include <json/json.h>

#include "models/Cart.h"
#include "models/MenuItem.h"
#include "models/Order.h"
#include "models/User.h"

namespace serialize
{
Json::Value toJson(const MenuCategory &c);
Json::Value toJson(const SizeOption &s);
Json::Value toJson(const AddOnOption &a);
Json::Value toJson(const MenuItem &item);
Json::Value toJson(const std::vector<MenuItem> &items);
Json::Value toJson(const std::vector<MenuCategory> &cats);

Json::Value toJson(const User &u);

Json::Value toJson(const CartItem &item);
Json::Value toJson(const Cart &cart);  // includes computed subtotal/itemCount

Json::Value toJson(const OrderItem &item);
Json::Value toJson(const Order &order);
Json::Value toJson(const std::vector<Order> &orders);
}  // namespace serialize
