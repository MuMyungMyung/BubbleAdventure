#pragma once
#include <functional>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/CollisionComponent.hpp"
class CollisionSystem {
  public:
    void checkCollisions(ComponentManager<CollisionComponent> &collisionManager,
        std::function<void(EntityManager::EntityID, EntityManager::EntityID)> onCollision);

  private:
    bool isColliding(const CollisionComponent &a, const CollisionComponent &b);
};
