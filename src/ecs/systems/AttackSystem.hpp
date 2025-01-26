#pragma once
#include <cmath>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/AttackComponent.hpp"
#include "ecs/components/HealthComponent.hpp"
#include "ecs/components/InputComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

class AttackSystem {
  public:
    void update(float deltaTime, ComponentManager<AttackComponent> &attackManager,
        ComponentManager<TransformComponent> &transformManager, ComponentManager<HealthComponent> &healthManager,
        ComponentManager<InputComponent> &inputManager);

  private:
    void performAttack(EntityManager::EntityID attacker, AttackComponent *attack,
        ComponentManager<TransformComponent> &transformManager, ComponentManager<HealthComponent> &healthManager);
};
