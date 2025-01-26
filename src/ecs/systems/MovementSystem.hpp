#pragma once
#include "ecs/ComponentManager.hpp"
#include "ecs/components/CollisionComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include "ecs/components/VelocityComponent.hpp"

class MovementSystem {
  public:
    void update(float deltaTime, ComponentManager<TransformComponent> &transformManager,
        ComponentManager<VelocityComponent> &velocityManager, ComponentManager<CollisionComponent> &collisionManager);
};
