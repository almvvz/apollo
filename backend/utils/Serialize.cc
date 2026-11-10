#include "Serialize.h"

namespace serialize
{
Json::Value toJson(const MenuCategory &c)
{
    Json::Value v;
    v["id"] = c.id;
    v["name"] = c.name;
    v["sortOrder"] = c.sortOrder;
    return v;
}

Json::Value toJson(const SizeOption &s)
{
    Json::Value v;
    v["id"] = s.id;
    v["label"] = s.label;
    v["priceDelta"] = s.priceDelta;
    return v;
}

Json::Value toJson(const AddOnOption &a)
{
    Json::Value v;
    v["id"] = a.id;
    v["label"] = a.label;
    v["priceDelta"] = a.priceDelta;
    return v;
}

Json::Value toJson(const MenuItem &item)
{
    Json::Value v;
    v["id"] = item.id;
    v["categoryId"] = item.categoryId;
    v["name"] = item.name;
    v["description"] = item.description;
    v["basePrice"] = item.basePrice;
    v["imageUrl"] = item.imageUrl;
    v["available"] = item.available;
    Json::Value sizes(Json::arrayValue);
    for (auto &s : item.sizes) sizes.append(toJson(s));
    v["sizes"] = sizes;
    Json::Value addOns(Json::arrayValue);
    for (auto &a : item.addOns) addOns.append(toJson(a));
    v["addOns"] = addOns;
    return v;
}

Json::Value toJson(const std::vector<MenuItem> &items)
{
    Json::Value arr(Json::arrayValue);
    for (auto &i : items) arr.append(toJson(i));
    return arr;
}

Json::Value toJson(const std::vector<MenuCategory> &cats)
{
    Json::Value arr(Json::arrayValue);
    for (auto &c : cats) arr.append(toJson(c));
    return arr;
}

Json::Value toJson(const User &u)
{
    Json::Value v;
    v["id"] = u.id;
    v["email"] = u.email;
    v["displayName"] = u.displayName;
    v["createdAt"] = u.createdAt;
    return v;
}

Json::Value toJson(const CartItem &item)
{
    Json::Value v;
    v["id"] = item.id;
    v["menuItemId"] = item.menuItemId;
    v["quantity"] = item.quantity;
    v["selectedSizeId"] = item.selectedSizeId;
    Json::Value addOns(Json::arrayValue);
    for (auto &id : item.selectedAddOnIds) addOns.append(id);
    v["selectedAddOnIds"] = addOns;
    v["lineTotal"] = item.lineTotal;
    return v;
}

Json::Value toJson(const Cart &cart)
{
    Json::Value v;
    Json::Value items(Json::arrayValue);
    double subtotal = 0.0;
    int itemCount = 0;
    for (auto &i : cart.items)
    {
        items.append(toJson(i));
        subtotal += i.lineTotal;
        itemCount += i.quantity;
    }
    v["items"] = items;
    v["subtotal"] = subtotal;
    v["itemCount"] = itemCount;
    return v;
}

Json::Value toJson(const OrderItem &item)
{
    Json::Value v;
    v["menuItemId"] = item.menuItemId;
    v["nameSnapshot"] = item.nameSnapshot;
    v["unitPriceSnapshot"] = item.unitPriceSnapshot;
    v["quantity"] = item.quantity;
    v["selectedSizeLabel"] = item.selectedSizeLabel;
    Json::Value addOns(Json::arrayValue);
    for (auto &label : item.selectedAddOnLabels) addOns.append(label);
    v["selectedAddOnLabels"] = addOns;
    v["lineTotal"] = item.lineTotal;
    return v;
}

Json::Value toJson(const Order &order)
{
    Json::Value v;
    v["id"] = order.id;
    Json::Value items(Json::arrayValue);
    for (auto &i : order.items) items.append(toJson(i));
    v["items"] = items;
    v["subtotal"] = order.subtotal;
    v["tax"] = order.tax;
    v["total"] = order.total;
    v["status"] = order.status;
    v["placedAt"] = order.placedAt;
    return v;
}

Json::Value toJson(const std::vector<Order> &orders)
{
    Json::Value arr(Json::arrayValue);
    for (auto &o : orders) arr.append(toJson(o));
    return arr;
}
}  // namespace serialize
