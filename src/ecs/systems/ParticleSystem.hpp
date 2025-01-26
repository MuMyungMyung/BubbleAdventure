#pragma once
#include <cmath>
#include "ecs/ComponentManager.hpp"
#include "ecs/components/ParticleEmitterComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class ParticleSystem {
  public:
    ParticleSystem(int maxParticles);

    void update(float deltaTime, ComponentManager<ParticleEmitterComponent> &particleEmitterManager,
        ComponentManager<TransformComponent> &transformManager);

    void render(SDL_Renderer *renderer);

  private:
    std::vector<Particle> particles;
    float initialLifetime = 1.0f;

    void emitParticles(TransformComponent &emitterTransform, ParticleEmitterComponent &emitter, float deltaTime);

    Particle *getInactiveParticle();

    float randomFloat(float min, float max);
};
