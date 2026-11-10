#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "models/Order.h"

struct OrderOpResult
{
    bool ok = false;
    std::string error;
    Order order;
};

class OrderStore
{
  public:
    static OrderStore &instance();

    // Snapshots the user's current cart into a new Order, computes totals,
    // and clears the cart. Fails if the cart is empty.
    OrderOpResult placeOrder(const std::string &userId);

    std::vector<Order> getOrders(const std::string &userId) const;  // newest first
    std::optional<Order> getOrder(const std::string &userId, const std::string &orderId) const;

  private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::vector<Order>> ordersByUserId_;
};
