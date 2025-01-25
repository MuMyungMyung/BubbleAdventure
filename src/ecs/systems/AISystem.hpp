#pragma once

#include <cmath>
#include "../ComponentManager.hpp"
#include "../components/AIComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/TagComponent.hpp"

class AISystem {
  public:
    void update(float deltaTime, ComponentManager<AIComponent> &aiManager,
        ComponentManager<PositionComponent> &positionManager, ComponentManager<HealthComponent> &healthManager,
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
                    if (shouldChase(entity, ai, positionManager, tagManager))
                        ai.currentState = AIComponent::State::Chase;
                    break;
                case AIComponent::State::Patrol:
                    if (ai.onPatrol)
                        ai.onPatrol();
                    if (shouldChase(entity, ai, positionManager, tagManager))
                        ai.currentState = AIComponent::State::Chase;
                    break;
                case AIComponent::State::Chase:
                    if (ai.onChase)
                        ai.onChase();
                    if (shouldFlee(entity, ai, healthManager, tagManager))
                        ai.currentState = AIComponent::State::Flee;
                    else if (shouldAttack(entity, ai, positionManager, tagManager))
                        ai.currentState = AIComponent::State::Attack;
                    else if (!shouldChase(entity, ai, positionManager, tagManager))
                        ai.currentState = AIComponent::State::Idle;
                    break;
                case AIComponent::State::Attack:
                    if (ai.onAttack)
                        ai.onAttack();
                    if (!shouldAttack(entity, ai, positionManager, tagManager))
                        ai.currentState = AIComponent::State::Chase;
                    break;
                case AIComponent::State::Flee:
                    if (ai.onFlee)
                        ai.onFlee();
                    break;
            }
        }
    }

  private:
    bool shouldFlee(EntityManager::EntityID aiEntity, AIComponent &ai, ComponentManager<HealthComponent> &healthManager,
        ComponentManager<TagComponent> &tagManager)
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

    bool shouldChase(EntityManager::EntityID aiEntity, AIComponent &ai,
        ComponentManager<PositionComponent> &positionManager, ComponentManager<TagComponent> &tagManager)
    {
        auto *aiPosition = positionManager.getComponent(aiEntity);
        for (auto &[entity, tag] : tagManager.getAllComponents()) {
            if (tag.tag != ai.targetTag)
                continue;
            auto *position = positionManager.getComponent(entity);

            if (aiPosition && position) {
                float distance =
                    std::sqrt(std::pow(position->x - aiPosition->x, 2) + std::pow(position->y - aiPosition->y, 2));
                if (distance <= ai.detectionRange) {
                    return true;
                }
            }
        }
        return false;
    }

    bool shouldAttack(EntityManager::EntityID aiEntity, AIComponent &ai,
        ComponentManager<PositionComponent> &positionManager, ComponentManager<TagComponent> &tagManager)
    {
        auto *aiPosition = positionManager.getComponent(aiEntity);
        for (auto &[entity, tag] : tagManager.getAllComponents()) {
            if (tag.tag != ai.targetTag)
                continue;
            auto *position = positionManager.getComponent(entity);

            if (aiPosition && position) {
                float distance =
                    std::sqrt(std::pow(position->x - aiPosition->x, 2) + std::pow(position->y - aiPosition->y, 2));
                if (distance <= ai.attackRange) {
                    return true;
                }
            }
        }
        return false;
    }
};
