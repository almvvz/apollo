#pragma once

#include <optional>
#include <shared_mutex>
#include <string>
#include <vector>

#include "models/MenuItem.h"

// In-memory menu catalog. Populated once at server boot from a static seed
// JSON file (see seed/menu_seed.json) and never written back to — this is
// NOT a database, just read-mostly RAM state, hence the shared_mutex rather
// than a per-write exclusive lock design.
class MenuStore
{
  public:
    static MenuStore &instance();

    // Loads seed content from the given path. Returns false (and leaves the
    // store with built-in fallback data) if the file can't be read/parsed.
    bool loadFromFile(const std::string &path);

    std::vector<MenuCategory> getCategories() const;
    std::vector<MenuItem> getItems(const std::optional<std::string> &categoryId = std::nullopt) const;
    std::optional<MenuItem> getItem(const std::string &itemId) const;

  private:
    void loadFallbackData();

    mutable std::shared_mutex mutex_;
    std::vector<MenuCategory> categories_;
    std::vector<MenuItem> items_;
};
