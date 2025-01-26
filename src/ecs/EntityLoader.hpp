#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "ecs/World.hpp"
#include "ecs/components/ItemComponent.hpp"

using json = nlohmann::json;

class EntityLoader {
  public:
    static void loadEntitiesFromJSON(const std::string &filename, World &world)
    {
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open json file " + filename);
        }
        json entitiesJson;

        try {
            file >> entitiesJson;
            file.close();
        } catch (const std::exception &e) {
            std::cerr << "Error while trying to parse entities json: " << e.what() << std::endl;
            file.close();
            return;
        }

        for (const auto &entityJson : entitiesJson) {
            auto entity = world.entityManager.createEntity();

            // Parse components
            if (entityJson.contains("components")) {
                const auto &components = entityJson["components"];
                std::cout << components << std::endl;

                // SpriteComponent
                if (components.contains("SpriteComponent")) {
                    auto sprite = components["SpriteComponent"];
                    SDL_FRect srcRect;
                    SDL_FRect dstRect;
                    if (sprite.contains("SourceRect")) {
                        auto sourceRect = sprite["SourceRect"];
                        srcRect.x = sourceRect.value("x", 0);
                        srcRect.y = sourceRect.value("y", 0);
                        srcRect.w = sourceRect.value("w", 0);
                        srcRect.h = sourceRect.value("h", 0);
                    }
                    if (sprite.contains("DestinationRect")) {
                        auto sourceRect = sprite["DestinationRect"];
                        srcRect.x = sourceRect.value("x", 0);
                        srcRect.y = sourceRect.value("y", 0);
                        srcRect.w = sourceRect.value("w", 0);
                        srcRect.h = sourceRect.value("h", 0);
                    }
                    SpriteComponent comp = SpriteComponent(sprite.value("texture", ""), srcRect, dstRect);
                    world.spriteManager.addComponent(entity, std::move(comp));
                }

                // StatsComponent
                if (components.contains("StatsComponent")) {
                    auto stats = components["StatsComponent"];
                    StatsComponent comp;
                    comp.attackPower = stats.value("attack", 0);
                    /* comp.currentHealth = stats.value("health", 0); */
                    comp.experience = stats.value("experience", 0);
                    comp.sanity = stats.value("sanity", 0);
                    world.statsManager.addComponent(entity, comp);
                }

                // SoundComponent
                if (components.contains("SoundComponent")) {
                    auto sound = components["SoundComponent"];
                    world.soundManager.addComponent(entity,
                        SoundComponent{
                            sound.value("soundEffects", std::vector<std::string>{}), sound.value("loop", false)});
                }

                // CollisionComponent
                if (components.contains("CollisionComponent")) {
                    auto collision = components["CollisionComponent"];
                    CollisionComponent comp;
                    comp.width = collision.value("width", 0);
                    comp.height = collision.value("height", 0);
                    comp.collisionLayer = collision.value("collisionLayer", 0);
                    comp.x = collision.value("x", 0);
                    comp.y = collision.value("y", 0);
                    comp.isStatic = collision.value("isStatic", true);
                    comp.isTrigger = collision.value("isTrigger", false);
                    world.collisionManager.addComponent(entity, comp);
                }

                // HealthComponent
                if (components.contains("HealthComponent")) {
                    auto health = components["HealthComponent"];
                    world.healthManager.addComponent(
                        entity, HealthComponent{health.value("currentHealth", 0), health.value("maxHealth", 0)});
                }

                // AIComponent
                if (components.contains("AIComponent")) {
                    auto ai = components["AIComponent"];
                    AIComponent comp;
                    comp.targetTag = ai.value("targetTag", "Player");
                    world.aiManager.addComponent(entity, comp);
                }
                if (components.contains("InputComponent")) {
                    auto input = components["InputComponent"];
                    InputComponent comp;
                    world.inputManager.addComponent(entity, comp);
                }
                if (components.contains("VelocityComponent")) {
                    auto velocity = components["VelocityComponent"];
                    VelocityComponent comp;
                    comp.dx = velocity.value("dx", 0);
                    comp.dy = velocity.value("dy", 0);
                    world.velocityManager.addComponent(entity, comp);
                }
                if (components.contains("TransformComponent")) {
                    auto transform = components["TransformComponent"];
                    TransformComponent comp;
                    comp.x = transform.value("x", 0);
                    comp.y = transform.value("y", 0);
                    comp.rotation = transform.value("rotation", 0);
                    comp.scale = transform.value("scale", 0);
                    world.transformManager.addComponent(entity, comp);
                }
                if (components.contains("TagComponent")) {
                    auto tag = components["TagComponent"];
                    TagComponent comp;
                    comp.tag = tag.value("tag", "Unknown");
                    world.tagManager.addComponent(entity, comp);
                }
                if (components.contains("ParticleEmitterComponent")) {
                    auto particleEmitter = components["ParticleEmitterComponent"];
                    ParticleEmitterComponent comp;
                    world.particleEmitterManager.addComponent(entity, comp);
                }
                if (components.contains("AttackComponent")) {
                    auto attack = components["AttackComponent"];
                    AttackComponent comp;
                    world.attackManager.addComponent(entity, comp);
                }
                if (components.contains("ItemComponent")) {
                    auto item = components["ItemComponent"];
                    ItemComponent comp;
                    world.itemManager.addComponent(entity, comp);
                }
            }
        }
    }
};
