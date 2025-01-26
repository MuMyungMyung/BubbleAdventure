#pragma once
#include "ecs/ComponentManager.hpp"
#include "ecs/components/ItemComponent.hpp"
#include "ecs/components/StatsComponent.hpp"

class ItemSystem {
  public:
    void onPickup(EntityManager::EntityID player, EntityManager::EntityID itemEntity,
        ComponentManager<ItemComponent> &itemManager, ComponentManager<StatsComponent> &statsManager,
        ComponentManager<HealthComponent> &healthManager);

  private:
    void applyItemEffects(const ItemComponent &item, StatsComponent &stats, HealthComponent &health);

    void addToInventory(EntityManager::EntityID, int);
};
