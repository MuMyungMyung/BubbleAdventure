#pragma once
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "TextureManager.hpp"
#include "components/AttackComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/ItemComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "ecs/components/SoundComponent.hpp"
#include "ecs/components/StatsComponent.hpp"
#include "ecs/systems/ParticleSystem.hpp"
#include "ecs/systems/SoundSystem.hpp"
#include "systems/AISystem.hpp"
#include "systems/AttackSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/InputSystem.hpp"
#include "systems/ItemSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "systems/StatSystem.hpp"
#include "systems/VelocitySystem.hpp"

class World {
  public:
    explicit World() : particleSystem(100)
    {
        soundSystem.loadSound("player_attack", "assets/sounds/bubblePopPopPop.wav");
    }
    EntityManager entityManager;
    ComponentManager<TransformComponent> transformManager;
    ComponentManager<VelocityComponent> velocityManager;
    ComponentManager<HealthComponent> healthManager;
    ComponentManager<InputComponent> inputManager;
    ComponentManager<AttackComponent> attackManager;
    ComponentManager<AIComponent> aiManager;
    ComponentManager<TagComponent> tagManager;
    ComponentManager<CollisionComponent> collisionManager;
    ComponentManager<ItemComponent> itemManager;
    ComponentManager<SpriteComponent> spriteManager;
    ComponentManager<ParticleEmitterComponent> particleEmitterManager;
    ComponentManager<StatsComponent> statsManager;
    ComponentManager<SoundComponent> soundManager;

    void removeEntity(EntityManager::EntityID id)
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

    void updateSystems(float deltaTime)
    {
        velocitySystem.update(inputManager, velocityManager);
        collisionSystem.checkCollisions(
            collisionManager, [this](EntityManager::EntityID left, EntityManager::EntityID right) {
                auto *leftVelocity = velocityManager.getComponent(left);
                auto *rightVelocity = velocityManager.getComponent(right);
                if (leftVelocity) {
                    leftVelocity->dx = -leftVelocity->dx;
                    leftVelocity->dy = -leftVelocity->dy;
                }
                if (rightVelocity) {
                    rightVelocity->dx = -rightVelocity->dx;
                    rightVelocity->dy = -rightVelocity->dy;
                }
            });
        movementSystem.update(deltaTime, transformManager, velocityManager, collisionManager);
        attackSystem.update(deltaTime, attackManager, transformManager, healthManager, inputManager);
        aiSystem.update(deltaTime, aiManager, transformManager, healthManager, tagManager);
        particleSystem.update(deltaTime, particleEmitterManager, transformManager);
        soundSystem.update(soundManager, transformManager, attackManager, tagManager);
    }

    void render(SDL_Renderer *renderer)
    {
        if (!renderer)
            return;
        spriteSystem.render(renderer, spriteManager, transformManager);
        particleSystem.render(renderer);
    }

    void handleEvents(const SDL_Event &event)
    {
        inputSystem.update(inputManager, event);
    }

  private:
    MovementSystem movementSystem;
    InputSystem inputSystem;
    VelocitySystem velocitySystem;
    AttackSystem attackSystem;
    AISystem aiSystem;
    StatSystem statSystem;
    CollisionSystem collisionSystem;
    ItemSystem itemSystem;
    SpriteSystem spriteSystem;
    ParticleSystem particleSystem;
    SoundSystem soundSystem;
};
