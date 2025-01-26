#include "World.hpp"

World::World() : particleSystem(100)
{
    soundSystem.loadSound("player_attack", "assets/sounds/bubblePopPopPop.wav");
}

void World::removeEntity(EntityManager::EntityID id)
{
    transformManager.removeComponent(id);
    velocityManager.removeComponent(id);
    healthManager.removeComponent(id);
    inputManager.removeComponent(id);
    attackManager.removeComponent(id);
    aiManager.removeComponent(id);
    tagManager.removeComponent(id);
    collisionManager.removeComponent(id);
    itemManager.removeComponent(id);
    spriteManager.removeComponent(id);
    particleEmitterManager.removeComponent(id);
    statsManager.removeComponent(id);
    soundManager.removeComponent(id);
    entityManager.destroyEntities(id);
}

void World::updateSystems(float deltaTime)
{
    velocitySystem.update(inputManager, velocityManager);
    collisionSystem.checkCollisions(
        collisionManager, [this, deltaTime](EntityManager::EntityID left, EntityManager::EntityID right) {
            auto *leftVelocity = velocityManager.getComponent(left);
            auto *rightVelocity = velocityManager.getComponent(right);
            auto *leftTransform = transformManager.getComponent(left);
            auto *rightTransform = transformManager.getComponent(right);
            if (leftVelocity && leftTransform) {
                leftVelocity->dx = -leftVelocity->dx;
                leftVelocity->dy = -leftVelocity->dy;
                leftTransform->x += leftVelocity->dx * deltaTime;
                leftTransform->y += leftVelocity->dy * deltaTime;
            }
            if (rightVelocity && rightTransform) {
                rightVelocity->dx = -rightVelocity->dx;
                rightVelocity->dy = -rightVelocity->dy;
                rightTransform->x += rightVelocity->dx * deltaTime;
                rightTransform->y += rightVelocity->dy * deltaTime;
            }
        });
    movementSystem.update(deltaTime, transformManager, velocityManager, collisionManager);
    attackSystem.update(deltaTime, attackManager, transformManager, healthManager, inputManager);
    aiSystem.update(deltaTime, aiManager, transformManager, healthManager, tagManager);
    particleSystem.update(deltaTime, particleEmitterManager, transformManager);
    soundSystem.update(soundManager, transformManager, attackManager, tagManager);
}

void World::render(SDL_Renderer *renderer)
{
    if (!renderer)
        return;
    spriteSystem.render(renderer, spriteManager, transformManager);
    particleSystem.render(renderer);
}

void World::handleEvents(const SDL_Event &event)
{
    inputSystem.update(inputManager, event);
}
