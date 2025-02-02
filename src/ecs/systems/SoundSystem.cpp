#include "SoundSystem.hpp"
SoundSystem::SoundSystem()
{
    m_mainAudio = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
}

SoundSystem::~SoundSystem()
{
    SDL_CloseAudioDevice(m_mainAudio);
    for (auto i : m_soundEffects) {
        SDL_DestroyAudioStream(i.second.stream);
        SDL_free(i.second.buffer);
    }
}

void SoundSystem::update(ComponentManager<SoundComponent> &soundManager,
    ComponentManager<TransformComponent> &transformManager, ComponentManager<AttackComponent> &attackManager,
    ComponentManager<TagComponent> &tagManager)
{
    for (auto &[entity, sound] : soundManager.getAllComponents()) {
        auto *transform = transformManager.getComponent(entity);
        auto *attack = attackManager.getComponent(entity);
        auto *tag = tagManager.getComponent(entity);

        if (!transform || !attack || !tag) {
            continue;
        }
        if (attack->isAttacking && tag->tag == "player") {
            for (auto i : sound.soundEffects) {
                loadSound("PlayerAttack", i);
                playSound("PlayerAttack");
            }
        }
    }
}

// Load a sound effect into memory
// TODO: Error handling
void SoundSystem::loadSound(const std::string &soundName, const std::string &filePath)
{
    if (m_soundEffects.find(soundName) != m_soundEffects.end())
        return;
    SDL_AudioSpec spec;
    SoundEffect sound;
    if (!SDL_LoadWAV(filePath.c_str(), &spec, &sound.buffer, &sound.len))
        return;
    sound.stream = SDL_CreateAudioStream(&spec, nullptr);
    if (!SDL_BindAudioStream(m_mainAudio, sound.stream)) {
        SDL_DestroyAudioStream(sound.stream);
        return;
    }
    m_soundEffects[soundName] = sound;
}

// Play a sound effect by name
void SoundSystem::playSound(const std::string &soundName)
{
    auto it = m_soundEffects.find(soundName);
    if (it != m_soundEffects.end()) {
        SDL_PutAudioStreamData(it->second.stream, it->second.buffer, it->second.len);
    } else {
        SDL_Log("Sound not found: %s", soundName.c_str());
    }
}

// Stop all playing sounds
void SoundSystem::stopAllSounds()
{
    for (auto i : m_soundEffects) {
        SDL_ClearAudioStream(i.second.stream);
    }
}

// Adjust volume of a specific sound effect
void SoundSystem::setSoundVolume(const std::string &soundName, float volume)
{
    auto it = m_soundEffects.find(soundName);
    if (it != m_soundEffects.end()) {
        SDL_SetAudioStreamGain(it->second.stream, volume);
    }
}

// Adjust the master volume for all streams
void SoundSystem::setMasterVolume(float volume)
{
    SDL_SetAudioDeviceGain(m_mainAudio, volume);
}
