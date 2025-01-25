#pragma once

#include <string>
#include <vector>

struct SoundComponent {
    std::vector<std::string> soundEffects; // List of sound effect file paths
    bool loop = false;                     // Whether the sound should loop
    int currentSoundIndex = -1;            // Index of the sound currently playing (-1 if none)
};
