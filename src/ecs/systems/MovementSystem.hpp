#pragma once
#include "ecs/ComponentManager.hpp"
#include "ecs/components/TransformComponent.hpp"
#include "ecs/components/VelocityComponent.hpp"

class MovementSystem {
  public:
    void update(float deltaTime, ComponentManager<TransformComponent> &transformManager,
        ComponentManager<VelocityComponent> &velocityManager)
    {
        for (auto &[entity, velocity] : velocityManager.getAllComponents()) {
            auto *transform = transformManager.getComponent(entity);

            if (transform) {
                transform->x += velocity.dx * deltaTime;
                transform->y += velocity.dy * deltaTime;
            }
        }
    }
};
