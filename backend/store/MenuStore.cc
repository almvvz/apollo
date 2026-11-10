#include "MenuStore.h"

#include <json/json.h>
#include <trantor/utils/Logger.h>

#include <fstream>

MenuStore &MenuStore::instance()
{
    static MenuStore store;
    return store;
}

bool MenuStore::loadFromFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        LOG_WARN << "Menu seed file not found at " << path << ", using fallback data";
        loadFallbackData();
        return false;
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    if (!Json::parseFromStream(builder, file, &root, &errs))
    {
        LOG_ERROR << "Failed to parse menu seed JSON: " << errs;
        loadFallbackData();
        return false;
    }

    std::vector<MenuCategory> categories;
    for (const auto &c : root["categories"])
    {
        categories.push_back({c["id"].asString(), c["name"].asString(), c["sortOrder"].asInt()});
    }

    std::vector<MenuItem> items;
    for (const auto &i : root["items"])
    {
        MenuItem item;
        item.id = i["id"].asString();
        item.categoryId = i["categoryId"].asString();
        item.name = i["name"].asString();
        item.description = i["description"].asString();
        item.basePrice = i["basePrice"].asDouble();
        item.imageUrl = i.get("imageUrl", "").asString();
        item.available = i.get("available", true).asBool();
        for (const auto &s : i["sizes"])
        {
            item.sizes.push_back({s["id"].asString(), s["label"].asString(), s["priceDelta"].asDouble()});
        }
        for (const auto &a : i["addOns"])
        {
            item.addOns.push_back({a["id"].asString(), a["label"].asString(), a["priceDelta"].asDouble()});
        }
        items.push_back(std::move(item));
    }

    std::unique_lock lock(mutex_);
    categories_ = std::move(categories);
    items_ = std::move(items);
    return true;
}

void MenuStore::loadFallbackData()
{
    std::unique_lock lock(mutex_);
    categories_ = {{"coffee", "Coffee", 0}};
    items_ = {{"house-brew",
               "coffee",
               "House Brew",
               "Our signature blend, brewed fresh.",
               6.9,
               "",
               {{"regular", "Regular", 0.0}, {"large", "Large", 1.5}},
               {{"extra-shot", "Extra Shot", 1.5}},
               true}};
}

std::vector<MenuCategory> MenuStore::getCategories() const
{
    std::shared_lock lock(mutex_);
    return categories_;
}

std::vector<MenuItem> MenuStore::getItems(const std::optional<std::string> &categoryId) const
{
    std::shared_lock lock(mutex_);
    if (!categoryId)
        return items_;

    std::vector<MenuItem> filtered;
    for (auto &item : items_)
    {
        if (item.categoryId == *categoryId)
            filtered.push_back(item);
    }
    return filtered;
}

std::optional<MenuItem> MenuStore::getItem(const std::string &itemId) const
{
    std::shared_lock lock(mutex_);
    for (auto &item : items_)
    {
        if (item.id == itemId)
            return item;
    }
    return std::nullopt;
}
