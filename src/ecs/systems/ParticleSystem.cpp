#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(int maxParticles)
{
    particles.resize(maxParticles);
}

void ParticleSystem::update(float deltaTime, ComponentManager<ParticleEmitterComponent> &particleEmitterManager,
    ComponentManager<TransformComponent> &transformManager)
{
    for (auto &particle : particles) {
        if (!particle.isActive)
            continue;

        particle.x += particle.vx * deltaTime;
        particle.y += particle.vy * deltaTime;
        particle.life -= deltaTime;

        particle.size = std::max(0.0f, particle.size - (deltaTime * 0.1f));
        particle.color.a = static_cast<Uint8>(255 * (particle.life / initialLifetime));

        if (particle.life <= 0)
            particle.isActive = false;
    }

    for (auto &[entity, particleEmitter] : particleEmitterManager.getAllComponents()) {
        auto *transform = transformManager.getComponent(entity);
        if (!transform)
            continue;
        emitParticles(*transform, particleEmitter, deltaTime);
    }
}

void ParticleSystem::render(SDL_Renderer *renderer)
{
    for (const auto &particle : particles) {
        if (!particle.isActive)
            continue;

        SDL_FRect rect{
            particle.x - particle.size / 2.0f, particle.y - particle.size / 2.0f, particle.size, particle.size};

        SDL_SetRenderDrawColor(renderer, particle.color.r, particle.color.g, particle.color.b, particle.color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void ParticleSystem::emitParticles(
    TransformComponent &emitterTransform, ParticleEmitterComponent &emitter, float deltaTime)
{
    emitter.timeSinceLastEmission += deltaTime;

    int particlesToEmit = static_cast<int>(emitter.emissionRate * emitter.timeSinceLastEmission);
    emitter.timeSinceLastEmission -= particlesToEmit / emitter.emissionRate;

    for (int i = 0; i < particlesToEmit; ++i) {
        auto *particle = getInactiveParticle();
        if (!particle)
            return;

        float angle = randomFloat(0, emitter.spreadAngle) * (M_PI / 180.0f);
        float speed = emitter.particleSpeed;

        particle->x = emitterTransform.x;
        particle->y = emitterTransform.y;
        particle->vx = std::cos(angle) * speed;
        particle->vy = std::sin(angle) * speed;
        particle->life = emitter.particleLifetime;
        particle->size = emitter.particleSize;
        particle->color = emitter.startColor;

        particle->isActive = true;
    }
}

Particle *ParticleSystem::getInactiveParticle()
{
    for (auto &particle : particles) {
        if (!particle.isActive)
            return &particle;
    }
    return nullptr;
}

float ParticleSystem::randomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
