#pragma once

#include <string>
#include <vector>

struct OrderItem
{
    std::string menuItemId;
    std::string nameSnapshot;
    double unitPriceSnapshot = 0.0;
    int quantity = 1;
    std::string selectedSizeLabel;
    std::vector<std::string> selectedAddOnLabels;
    double lineTotal = 0.0;
};

struct Order
{
    std::string id;
    std::string userId;
    std::vector<OrderItem> items;
    double subtotal = 0.0;
    double tax = 0.0;
    double total = 0.0;
    std::string status = "placed";
    std::string placedAt;  // ISO-8601
};
