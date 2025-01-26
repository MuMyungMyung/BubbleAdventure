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
    explicit World();
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

    void removeEntity(EntityManager::EntityID id);

    void updateSystems(float deltaTime);

    void render(SDL_Renderer *renderer);

    void handleEvents(const SDL_Event &event);

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
