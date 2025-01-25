#pragma once

#include <SDL3/SDL_pixels.h>
struct Particle {
    float x, y;          // Position of the particle
    float vx, vy;        // Velocity of the particle
    float life;          // Remaining lifetime (in seconds)
    float size;          // Size of the particle
    float rotation;      // Rotation angle (if applicable)
    float rotationSpeed; // Speed of rotation
    SDL_Color color;     // Particle color (optional for visual variety)

    bool isActive = true; // Whether the particle is active
};

struct ParticleEmitterComponent {
    int maxParticles;       // Maximum number of particles to emit
    float emissionRate;     // Particles emitted per second
    float particleLifetime; // Lifetime of each particle
    float particleSpeed;    // Speed of emitted particles
    float particleSize;     // Size of each particle
    SDL_Color startColor;   // Starting color of particles
    SDL_Color endColor;     // Ending color of particles (optional)
    float spreadAngle;      // Spread angle in degrees (e.g., 360 for full circle)

    float timeSinceLastEmission = 0; // Internal timer for emission tracking
};
