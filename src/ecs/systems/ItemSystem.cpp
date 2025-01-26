#include "ItemSystem.hpp"

void ItemSystem::onPickup(EntityManager::EntityID player, EntityManager::EntityID itemEntity,
    ComponentManager<ItemComponent> &itemManager, ComponentManager<StatsComponent> &statsManager,
    ComponentManager<HealthComponent> &healthManager)
{
    auto *item = itemManager.getComponent(itemEntity);
    auto *stats = statsManager.getComponent(player);
    auto *health = healthManager.getComponent(player);
    if (!item || !stats)
        return;

    if (item->type == ItemComponent::ItemType::Consumable) {
        applyItemEffects(*item, *stats, *health);
    }

    if (item->isUsedOnPickup) {
        itemManager.removeComponent(itemEntity);
    } else {
        addToInventory(player, item->itemID);
    }
}

void ItemSystem::applyItemEffects(const ItemComponent &item, StatsComponent &stats, HealthComponent &health)
{
    health.currentHealth += item.effect.healthRestore;
    if (health.currentHealth > health.maxHealth)
        health.currentHealth = health.maxHealth;
    stats.sanity += item.effect.sanityRestore;
    if (stats.sanity > stats.maxSanity)
        stats.sanity = stats.maxSanity;
}

void ItemSystem::addToInventory(EntityManager::EntityID, int)
{
    // TODO
}
