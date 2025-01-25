#pragma once

#include <string>

struct ItemComponent {
    // General properties
    std::string name;        // Name of the item (e.g., "Health Potion")
    std::string description; // Optional: Description for tooltips or logs
    int itemID;              // Unique identifier for the item (useful for inventory or spawning)

    // Item type or behavior
    enum class ItemType {
        Consumable, // Items like health or sanity potions
        Weapon,     // Equipable weapons
        KeyItem,    // Important items for progression
    } type;

    // Effect data for consumables
    struct Effect {
        int healthRestore = 0; // Health points to restore
        int sanityRestore = 0; // Sanity points to restore
    } effect;

    // Other properties
    bool isPickupable = true;    // Whether the item can be picked up
    bool isUsedOnPickup = false; // If true, automatically applies its effect when picked up
};
