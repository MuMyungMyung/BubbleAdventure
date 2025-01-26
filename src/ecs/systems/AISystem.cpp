#include "AISystem.hpp"
#include <iostream>
void AISystem::update(float deltaTime, ComponentManager<AIComponent> &aiManager,
    ComponentManager<TransformComponent> &transformManager, ComponentManager<HealthComponent> &healthManager,
    ComponentManager<TagComponent> &tagManager)
{
    for (auto &[entity, ai] : aiManager.getAllComponents()) {
        ai.decisionTimer += deltaTime;

        if (ai.decisionTimer < ai.decisionInterval)
            continue;

        ai.decisionTimer = 0.0f;

        switch (ai.currentState) {
            case AIComponent::State::Idle:
                if (ai.onIdle)
                    ai.onIdle();
                if (shouldChase(entity, ai, transformManager, tagManager))
                    ai.currentState = AIComponent::State::Chase;
                break;
            case AIComponent::State::Patrol:
                if (ai.onPatrol)
                    ai.onPatrol();
                if (shouldChase(entity, ai, transformManager, tagManager))
                    ai.currentState = AIComponent::State::Chase;
                break;
            case AIComponent::State::Chase:
                if (ai.onChase)
                    ai.onChase();
                if (shouldFlee(entity, ai, healthManager, tagManager))
                    ai.currentState = AIComponent::State::Flee;
                else if (shouldAttack(entity, ai, transformManager, tagManager))
                    ai.currentState = AIComponent::State::Attack;
                else if (!shouldChase(entity, ai, transformManager, tagManager))
                    ai.currentState = AIComponent::State::Idle;
                break;
            case AIComponent::State::Attack:
                if (ai.onAttack)
                    ai.onAttack();
                if (!shouldAttack(entity, ai, transformManager, tagManager))
                    ai.currentState = AIComponent::State::Chase;
                break;
            case AIComponent::State::Flee:
                if (ai.onFlee)
                    ai.onFlee();
                break;
        }
    }
}

bool AISystem::shouldFlee(EntityManager::EntityID aiEntity, AIComponent &ai,
    ComponentManager<HealthComponent> &healthManager, ComponentManager<TagComponent> &tagManager)
{
    auto *aiHealth = healthManager.getComponent(aiEntity);
    for (auto &[entity, tag] : tagManager.getAllComponents()) {
        if (tag.tag != ai.targetTag)
            continue;
        auto *health = healthManager.getComponent(entity);

        if (aiHealth < health) {
            return true;
        }
    }
    return false;
}

bool AISystem::shouldChase(EntityManager::EntityID aiEntity, AIComponent &ai,
    ComponentManager<TransformComponent> &transformManager, ComponentManager<TagComponent> &tagManager)
{
    auto *aiTransform = transformManager.getComponent(aiEntity);
    for (auto &[entity, tag] : tagManager.getAllComponents()) {
        if (tag.tag != ai.targetTag)
            continue;
        auto *transform = transformManager.getComponent(entity);

        if (aiTransform && transform) {
            float distance =
                std::sqrt(std::pow(transform->x - aiTransform->x, 2) + std::pow(transform->y - aiTransform->y, 2));
            if (distance <= ai.detectionRange * 32) {
                return true;
            }
        }
    }
    return false;
}

bool AISystem::shouldAttack(EntityManager::EntityID aiEntity, AIComponent &ai,
    ComponentManager<TransformComponent> &transformManager, ComponentManager<TagComponent> &tagManager)
{
    auto *aiTransform = transformManager.getComponent(aiEntity);
    for (auto &[entity, tag] : tagManager.getAllComponents()) {
        if (tag.tag != ai.targetTag)
            continue;
        auto *transform = transformManager.getComponent(entity);

        if (aiTransform && transform) {
            float distance =
                std::sqrt(std::pow(transform->x - aiTransform->x, 2) + std::pow(transform->y - aiTransform->y, 2));
            if (distance <= ai.attackRange * 32) {
                return true;
            }
        }
    }
    return false;
}
