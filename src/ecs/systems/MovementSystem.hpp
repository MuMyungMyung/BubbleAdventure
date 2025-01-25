#pragma once
#include "../ComponentManager.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/VelocityComponent.hpp"

class MovementSystem {
  public:
    void update(float deltaTime, ComponentManager<PositionComponent> &positionManager,
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
