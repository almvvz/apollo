#include "CartStore.h"

#include <algorithm>

#include "MenuStore.h"
#include "utils/IdGen.h"

namespace
{
// Validates the given selection against the current menu item and computes
// the resulting line total. Returns nullopt and sets errorOut on failure.
std::optional<double> computeLineTotal(const MenuItem &item,
                                        const std::string &selectedSizeId,
                                        const std::vector<std::string> &selectedAddOnIds,
                                        int quantity,
                                        std::string &errorOut)
{
    if (!item.available)
    {
        errorOut = "menu item is unavailable";
        return std::nullopt;
    }
    if (quantity < 1)
    {
        errorOut = "quantity must be at least 1";
        return std::nullopt;
    }

    double price = item.basePrice;

    if (!item.sizes.empty())
    {
        const SizeOption *size = item.findSize(selectedSizeId);
        if (!size)
        {
            errorOut = "invalid size selection";
            return std::nullopt;
        }
        price += size->priceDelta;
    }

    for (const auto &addOnId : selectedAddOnIds)
    {
        const AddOnOption *addOn = item.findAddOn(addOnId);
        if (!addOn)
        {
            errorOut = "invalid add-on selection";
            return std::nullopt;
        }
        price += addOn->priceDelta;
    }

    return price * quantity;
}
}  // namespace

CartStore &CartStore::instance()
{
    static CartStore store;
    return store;
}

Cart CartStore::getCart(const std::string &userId) const
{
    std::lock_guard lock(mutex_);
    auto it = cartsByUserId_.find(userId);
    if (it == cartsByUserId_.end())
        return Cart{userId, {}};
    return it->second;
}

CartOpResult CartStore::addItem(const std::string &userId,
                                 const std::string &menuItemId,
                                 int quantity,
                                 const std::string &selectedSizeId,
                                 const std::vector<std::string> &selectedAddOnIds)
{
    auto menuItem = MenuStore::instance().getItem(menuItemId);
    if (!menuItem)
        return {false, "menu item not found", {}};

    std::string error;
    auto lineTotal =
        computeLineTotal(*menuItem, selectedSizeId, selectedAddOnIds, quantity, error);
    if (!lineTotal)
        return {false, error, {}};

    CartItem cartItem;
    cartItem.id = idgen::randomHex(8);
    cartItem.menuItemId = menuItemId;
    cartItem.quantity = quantity;
    cartItem.selectedSizeId = selectedSizeId;
    cartItem.selectedAddOnIds = selectedAddOnIds;
    cartItem.lineTotal = *lineTotal;

    std::lock_guard lock(mutex_);
    auto &cart = cartsByUserId_[userId];
    cart.userId = userId;
    cart.items.push_back(std::move(cartItem));
    return {true, "", cart};
}

CartOpResult CartStore::updateItem(const std::string &userId,
                                    const std::string &cartItemId,
                                    std::optional<int> quantity,
                                    std::optional<std::string> selectedSizeId,
                                    std::optional<std::vector<std::string>> selectedAddOnIds)
{
    std::lock_guard lock(mutex_);
    auto cartIt = cartsByUserId_.find(userId);
    if (cartIt == cartsByUserId_.end())
        return {false, "cart item not found", {}};

    auto &items = cartIt->second.items;
    auto itemIt = std::find_if(
        items.begin(), items.end(), [&](const CartItem &i) { return i.id == cartItemId; });
    if (itemIt == items.end())
        return {false, "cart item not found", {}};

    auto menuItem = MenuStore::instance().getItem(itemIt->menuItemId);
    if (!menuItem)
        return {false, "menu item no longer available", {}};

    int newQuantity = quantity.value_or(itemIt->quantity);
    std::string newSizeId = selectedSizeId.value_or(itemIt->selectedSizeId);
    std::vector<std::string> newAddOnIds = selectedAddOnIds.value_or(itemIt->selectedAddOnIds);

    std::string error;
    auto lineTotal = computeLineTotal(*menuItem, newSizeId, newAddOnIds, newQuantity, error);
    if (!lineTotal)
        return {false, error, {}};

    itemIt->quantity = newQuantity;
    itemIt->selectedSizeId = newSizeId;
    itemIt->selectedAddOnIds = newAddOnIds;
    itemIt->lineTotal = *lineTotal;

    return {true, "", cartIt->second};
}

CartOpResult CartStore::removeItem(const std::string &userId, const std::string &cartItemId)
{
    std::lock_guard lock(mutex_);
    auto cartIt = cartsByUserId_.find(userId);
    if (cartIt == cartsByUserId_.end())
        return {false, "cart item not found", {}};

    auto &items = cartIt->second.items;
    auto before = items.size();
    items.erase(std::remove_if(items.begin(),
                                items.end(),
                                [&](const CartItem &i) { return i.id == cartItemId; }),
                items.end());
    if (items.size() == before)
        return {false, "cart item not found", {}};

    return {true, "", cartIt->second};
}

Cart CartStore::clearCart(const std::string &userId)
{
    std::lock_guard lock(mutex_);
    cartsByUserId_[userId] = Cart{userId, {}};
    return cartsByUserId_[userId];
}
