#pragma once

#include <cmath>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/AIComponent.hpp"
#include "ecs/components/HealthComponent.hpp"
#include "ecs/components/TagComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

class AISystem {
  public:
    void update(float deltaTime, ComponentManager<AIComponent> &aiManager,
        ComponentManager<TransformComponent> &transformManager, ComponentManager<HealthComponent> &healthManager,
        ComponentManager<TagComponent> &tagManager);

  private:
    bool shouldFlee(EntityManager::EntityID aiEntity, AIComponent &ai, ComponentManager<HealthComponent> &healthManager,
        ComponentManager<TagComponent> &tagManager);

    bool shouldChase(EntityManager::EntityID aiEntity, AIComponent &ai,
        ComponentManager<TransformComponent> &transformManager, ComponentManager<TagComponent> &tagManager);

    bool shouldAttack(EntityManager::EntityID aiEntity, AIComponent &ai,
        ComponentManager<TransformComponent> &transformManager, ComponentManager<TagComponent> &tagManager);
};
