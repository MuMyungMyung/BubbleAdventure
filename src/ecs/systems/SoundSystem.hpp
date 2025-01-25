#pragma once

#include "ecs/components/SoundComponent.hpp"

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

class SoundSystem {
  public:
    SoundSystem()
    {
    }

    ~SoundSystem()
    {
        // Clean up sound effects and music
        for (auto &[key, sound] : soundEffects) {}
        soundEffects.clear();
    }

    // Load a sound effect into memory
    void loadSound(const std::string &soundName, const std::string &filePath)
    {
    }

    // Play a sound effect by name
    void playSound(const std::string &soundName, bool loop = false)
    {
        auto it = soundEffects.find(soundName);
        if (it != soundEffects.end()) {
            int loops = loop ? -1 : 0; // -1 for infinite looping
        } else {
            SDL_Log("Sound not found: %s", soundName.c_str());
        }
    }

    // Stop all playing sounds
    void stopAllSounds()
    {
    }

    // Adjust volume of a specific sound effect (0 to 128)
    void setSoundVolume(const std::string &soundName, int volume)
    {
        auto it = soundEffects.find(soundName);
        if (it != soundEffects.end()) {}
    }

    // Adjust the master volume for all channels
    void setMasterVolume(int volume)
    {
    }

  private:
    std::unordered_map<std::string, void *> soundEffects; // Stores sound effects by name
};
