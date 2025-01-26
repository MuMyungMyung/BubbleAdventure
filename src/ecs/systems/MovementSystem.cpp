#include "MovementSystem.hpp"
#include "ecs/components/CollisionComponent.hpp"

void MovementSystem::update(float deltaTime, ComponentManager<TransformComponent> &transformManager,
    ComponentManager<VelocityComponent> &velocityManager, ComponentManager<CollisionComponent> &collisionManager)
{
    for (auto &[entity, velocity] : velocityManager.getAllComponents()) {
        auto *transform = transformManager.getComponent(entity);
        auto *collision = collisionManager.getComponent(entity);

        if (transform) {
            transform->x += velocity.dx * deltaTime;
            transform->y += velocity.dy * deltaTime;
        }
        if (collision && transform) {
            collision->x = transform->x;
            collision->y = transform->y;
        }
    }
}
