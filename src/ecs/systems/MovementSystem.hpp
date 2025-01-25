#pragma once
#include "ecs/ComponentManager.hpp"
#include "ecs/components/TransformComponent.hpp"
#include "ecs/components/VelocityComponent.hpp"

class MovementSystem {
  public:
    void update(float deltaTime, ComponentManager<TransformComponent> &positionManager,
        ComponentManager<VelocityComponent> &velocityManager)
    {
        for (auto &[entity, velocity] : velocityManager.getAllComponents()) {
            auto *position = positionManager.getComponent(entity);

            if (position) {
                position->x += velocity.dx * deltaTime;
                position->y += velocity.dy * deltaTime;
            }
        }
    }
};
