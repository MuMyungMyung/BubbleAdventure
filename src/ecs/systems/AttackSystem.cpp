#include "AttackSystem.hpp"

void AttackSystem::update(float deltaTime, ComponentManager<AttackComponent> &attackManager,
    ComponentManager<TransformComponent> &transformManager, ComponentManager<HealthComponent> &healthManager,
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
                performAttack(entity, attack, transformManager, healthManager);
                attack->resetCooldown();
                attack->isAttacking = true;
            } else {
                attack->isAttacking = false;
            }
        }
    }
}

void AttackSystem::performAttack(EntityManager::EntityID attacker, AttackComponent *attack,
    ComponentManager<TransformComponent> &transformManager, ComponentManager<HealthComponent> &healthManager)
{
    auto *attackerTransform = transformManager.getComponent(attacker);

    if (!attackerTransform)
        return;

    for (auto &[entity, health] : healthManager.getAllComponents()) {
        if (entity == attacker)
            continue;

        auto *targetTransform = transformManager.getComponent(entity);

        if (!targetTransform)
            continue;

        float distance = std::sqrt(std::pow(targetTransform->x - attackerTransform->x, 2)
            + std::pow(targetTransform->y - attackerTransform->y, 2));

        if (distance <= attack->range) {
            health.currentHealth -= attack->damage;
            if (health.currentHealth < 0)
                health.currentHealth = 0;
        }
    }
}
