#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "models/Cart.h"

struct CartOpResult
{
    bool ok = false;
    std::string error;
    Cart cart;
};

// Cart state is partitioned per-user in RAM. Prices are always recomputed
// server-side from the current MenuStore contents — the client never sends
// a trusted price.
class CartStore
{
  public:
    static CartStore &instance();

    Cart getCart(const std::string &userId) const;

    CartOpResult addItem(const std::string &userId,
                          const std::string &menuItemId,
                          int quantity,
                          const std::string &selectedSizeId,
                          const std::vector<std::string> &selectedAddOnIds);

    CartOpResult updateItem(const std::string &userId,
                             const std::string &cartItemId,
                             std::optional<int> quantity,
                             std::optional<std::string> selectedSizeId,
                             std::optional<std::vector<std::string>> selectedAddOnIds);

    CartOpResult removeItem(const std::string &userId, const std::string &cartItemId);

    Cart clearCart(const std::string &userId);

  private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, Cart> cartsByUserId_;
};
