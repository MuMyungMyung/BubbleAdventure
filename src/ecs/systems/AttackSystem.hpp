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
        ComponentManager<TransformComponent> &positionManager, ComponentManager<HealthComponent> &healthManager,
        ComponentManager<InputComponent> &inputManager)
    {
        for (auto &[entity, health] : healthManager.getAllComponents()) {
            auto *attack = attackManager.getComponent(entity);
            if (!attack)
                continue;
            attack->updateCooldown(deltaTime);

            if (attack->canAttack()) {
                auto *input = inputManager.getComponent(entity);
                if (input && input->isActionActive(InputAction::Attack)) {
                    performAttack(entity, attack, positionManager, healthManager);
                    attack->resetCooldown();
                    attack->isAttacking = true;
                } else {
                    attack->isAttacking = false;
                }
            }
        }
    }

  private:
    void performAttack(EntityManager::EntityID attacker, AttackComponent *attack,
        ComponentManager<TransformComponent> &positionManager, ComponentManager<HealthComponent> &healthManager)
    {
        auto *attackerPosition = positionManager.getComponent(attacker);

        if (!attackerPosition)
            return;

        for (auto &[entity, health] : healthManager.getAllComponents()) {
            if (entity == attacker)
                continue;

            auto *targetPosition = positionManager.getComponent(entity);

            if (!targetPosition)
                continue;

            float distance = std::sqrt(std::pow(targetPosition->x - attackerPosition->x, 2)
                + std::pow(targetPosition->y - attackerPosition->y, 2));

            if (distance <= attack->range) {
                health.currentHealth -= attack->damage;
                if (health.currentHealth < 0)
                    health.currentHealth = 0;
            }
        }
    }
};
