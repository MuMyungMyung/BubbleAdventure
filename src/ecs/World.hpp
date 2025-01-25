#pragma once
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
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
    }
    EntityManager entityManager;
    ComponentManager<TransformComponent> positionManager;
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

    void updateSystems(float deltaTime)
    {
        velocitySystem.update(inputManager, velocityManager);
        movementSystem.update(deltaTime, positionManager, velocityManager);
        attackSystem.update(deltaTime, attackManager, positionManager, healthManager, inputManager);
        aiSystem.update(deltaTime, aiManager, positionManager, healthManager, tagManager);
        collisionSystem.checkCollisions(collisionManager, nullptr); // TODO
        particleSystem.update(deltaTime, particleEmitterManager, positionManager);
    }

    void render(SDL_Renderer *renderer)
    {
        if (!renderer)
            return;
        spriteSystem.render(renderer, spriteManager, positionManager);
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
};
