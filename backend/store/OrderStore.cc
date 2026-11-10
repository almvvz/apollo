#include "OrderStore.h"

#include <algorithm>

#include "CartStore.h"
#include "MenuStore.h"
#include "utils/IdGen.h"

namespace
{
constexpr double kTaxRate = 0.06;  // flat demo tax rate (approximates Malaysian SST)
}

OrderStore &OrderStore::instance()
{
    static OrderStore store;
    return store;
}

OrderOpResult OrderStore::placeOrder(const std::string &userId)
{
    Cart cart = CartStore::instance().getCart(userId);
    if (cart.items.empty())
        return {false, "cart is empty", {}};

    Order order;
    order.id = idgen::randomHex(12);
    order.userId = userId;
    order.placedAt = idgen::isoNow();

    for (const auto &cartItem : cart.items)
    {
        auto menuItem = MenuStore::instance().getItem(cartItem.menuItemId);
        if (!menuItem)
            continue;  // menu item removed since being added to cart; skip snapshotting it

        OrderItem orderItem;
        orderItem.menuItemId = cartItem.menuItemId;
        orderItem.nameSnapshot = menuItem->name;
        orderItem.unitPriceSnapshot =
            cartItem.quantity > 0 ? cartItem.lineTotal / cartItem.quantity : menuItem->basePrice;
        orderItem.quantity = cartItem.quantity;
        if (const SizeOption *size = menuItem->findSize(cartItem.selectedSizeId))
            orderItem.selectedSizeLabel = size->label;
        for (const auto &addOnId : cartItem.selectedAddOnIds)
        {
            if (const AddOnOption *addOn = menuItem->findAddOn(addOnId))
                orderItem.selectedAddOnLabels.push_back(addOn->label);
        }
        orderItem.lineTotal = cartItem.lineTotal;

        order.items.push_back(std::move(orderItem));
        order.subtotal += cartItem.lineTotal;
    }

    order.tax = order.subtotal * kTaxRate;
    order.total = order.subtotal + order.tax;

    {
        std::lock_guard lock(mutex_);
        ordersByUserId_[userId].push_back(order);
    }

    CartStore::instance().clearCart(userId);

    return {true, "", order};
}

std::vector<Order> OrderStore::getOrders(const std::string &userId) const
{
    std::lock_guard lock(mutex_);
    auto it = ordersByUserId_.find(userId);
    if (it == ordersByUserId_.end())
        return {};

    std::vector<Order> orders = it->second;
    std::reverse(orders.begin(), orders.end());  // newest first
    return orders;
}

std::optional<Order> OrderStore::getOrder(const std::string &userId, const std::string &orderId) const
{
    std::lock_guard lock(mutex_);
    auto it = ordersByUserId_.find(userId);
    if (it == ordersByUserId_.end())
        return std::nullopt;

    for (const auto &order : it->second)
    {
        if (order.id == orderId)
            return order;
    }
    return std::nullopt;
}
