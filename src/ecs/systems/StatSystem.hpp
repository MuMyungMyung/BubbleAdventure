#pragma once
#include "ecs/ComponentManager.hpp"
#include "ecs/components/StatsComponent.hpp"

class StatSystem {
  public:
    void gainExperience(EntityManager::EntityID entity, int xp, ComponentManager<StatsComponent> statsManager,
        ComponentManager<HealthComponent> &healthManager)
    {
        auto *stats = statsManager.getComponent(entity);
        if (!stats)
            return;
        stats->gainExperience(xp, healthManager, entity);
    }

    void modifySanity(EntityManager::EntityID entity, int amount, ComponentManager<StatsComponent> &statsManager)
    {
        auto *stats = statsManager.getComponent(entity);
        if (!stats)
            return;
        stats->sanity += amount;
        if (stats->sanity > stats->maxSanity)
            stats->sanity = stats->maxSanity;
        if (stats->sanity < 0)
            stats->sanity = 0;
    }
};
