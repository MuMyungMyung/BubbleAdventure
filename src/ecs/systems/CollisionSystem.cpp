#include "CollisionSystem.hpp"
#include <iostream>
#include <ostream>

void CollisionSystem::checkCollisions(ComponentManager<CollisionComponent> &collisionManager,
    std::function<void(EntityManager::EntityID, EntityManager::EntityID)> onCollision)
{
    // Get all entities with a CollisionComponent
    auto entities = collisionManager.getAllEntities();

    for (size_t i = 0; i < entities.size(); i++) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            auto *colA = collisionManager.getComponent(entities[i]);
            auto *colB = collisionManager.getComponent(entities[j]);

            if (!colA || !colB)
                continue;

            if (isColliding(*colA, *colB) && colA->collisionLayer != colB->collisionLayer) {
                std::cout << "isColliding" << std::endl;
                if (onCollision)
                    onCollision(entities[i], entities[j]);
            }
        }
    }
}

bool CollisionSystem::isColliding(const CollisionComponent &a, const CollisionComponent &b)
{
    return !(a.x + a.width < b.x || // a is to the left of b
        a.x > b.x + b.width ||      // a is to the right of b
        a.y + a.height < b.y ||     // a is above b
        a.y > b.y + b.height);      // a is below b
}
