#include "MovementSystem.hpp"

void MovementSystem::update(float deltaTime, ComponentManager<TransformComponent> &transformManager,
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
