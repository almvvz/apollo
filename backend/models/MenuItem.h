#pragma once

#include <string>
#include <vector>

struct SizeOption
{
    std::string id;
    std::string label;
    double priceDelta = 0.0;
};

struct AddOnOption
{
    std::string id;
    std::string label;
    double priceDelta = 0.0;
};

struct MenuCategory
{
    std::string id;
    std::string name;
    int sortOrder = 0;
};

struct MenuItem
{
    std::string id;
    std::string categoryId;
    std::string name;
    std::string description;
    double basePrice = 0.0;
    std::string imageUrl;
    std::vector<SizeOption> sizes;
    std::vector<AddOnOption> addOns;
    bool available = true;

    const SizeOption *findSize(const std::string &sizeId) const
    {
        for (auto &s : sizes)
            if (s.id == sizeId)
                return &s;
        return nullptr;
    }

    const AddOnOption *findAddOn(const std::string &addOnId) const
    {
        for (auto &a : addOns)
            if (a.id == addOnId)
                return &a;
        return nullptr;
    }
};
