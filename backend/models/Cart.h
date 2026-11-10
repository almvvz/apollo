#pragma once

#include <string>
#include <vector>

struct CartItem
{
    std::string id;
    std::string menuItemId;
    int quantity = 1;
    std::string selectedSizeId;
    std::vector<std::string> selectedAddOnIds;
    double lineTotal = 0.0;  // computed server-side from current menu prices
};

struct Cart
{
    std::string userId;
    std::vector<CartItem> items;
};
