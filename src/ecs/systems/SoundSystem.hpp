#pragma once

#include "ecs/ComponentManager.hpp"
#include "ecs/components/AttackComponent.hpp"
#include "ecs/components/SoundComponent.hpp"
#include "ecs/components/TagComponent.hpp"
#include "ecs/components/TransformComponent.hpp"

#include <SDL3/SDL.h>
#include <string>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_system.h>
#include <unordered_map>

class SoundSystem {
  public:
    SoundSystem();

    ~SoundSystem();

    void update(ComponentManager<SoundComponent> &soundManager, ComponentManager<TransformComponent> &transformManager,
        ComponentManager<AttackComponent> &attackManager, ComponentManager<TagComponent> &tagManager);

    // Load a sound effect into memory
    // TODO: Error handling
    void loadSound(const std::string &soundName, const std::string &filePath);

  private:
    // Play a sound effect by name
    void playSound(const std::string &soundName);

    // Stop all playing sounds
    void stopAllSounds();

    // Adjust volume of a specific sound effect
    void setSoundVolume(const std::string &soundName, float volume);

    // Adjust the master volume for all streams
    void setMasterVolume(float volume);

    struct SoundEffect {
        Uint8 *buffer = nullptr;
        Uint32 len = 0;
        SDL_AudioStream *stream = nullptr;
    };
    std::unordered_map<std::string, SoundEffect> m_soundEffects;
    SDL_AudioDeviceID m_mainAudio;
};
