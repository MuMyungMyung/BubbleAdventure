#pragma once
#include "ecs/ComponentManager.hpp"
#include "ecs/components/StatsComponent.hpp"

class StatSystem {
  public:
    void gainExperience(EntityManager::EntityID entity, int xp, ComponentManager<StatsComponent> statsManager,
        ComponentManager<HealthComponent> &healthManager);

    void modifySanity(EntityManager::EntityID entity, int amount, ComponentManager<StatsComponent> &statsManager);
};
