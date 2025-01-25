#pragma once
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "components/AttackComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/InputComponent.hpp"
#include "components/ItemComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"
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
    EntityManager entityManager;
    ComponentManager<PositionComponent> positionManager;
    ComponentManager<VelocityComponent> velocityManager;
    ComponentManager<HealthComponent> healthManager;
    ComponentManager<InputComponent> inputManager;
    ComponentManager<AttackComponent> attackManager;
    ComponentManager<AIComponent> aiManager;
    ComponentManager<TagComponent> tagManager;
    ComponentManager<CollisionComponent> collisionManager;
    ComponentManager<ItemComponent> itemManager;
    ComponentManager<SpriteComponent> spriteManager;

    void updateSystems(float deltaTime)
    {
        inputSystem.update(inputManager, deltaTime);
        velocitySystem.update(deltaTime, inputManager, velocityManager);
        movementSystem.update(deltaTime, positionManager, velocityManager);
        attackSystem.update(deltaTime, attackManager, positionManager, healthManager, inputManager);
        aiSystem.update(deltaTime, aiManager, positionManager, healthManager, tagManager);
        collisionSystem.checkCollisions(collisionManager, nullptr); // TODO
        spriteSystem.Render(renderer, spriteManager, positionManager);
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

    SDL_Renderer *renderer;
};
