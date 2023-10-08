#include "sound.h"
#include "SDL2/SDL_log.h"

SoundManager::SoundManager(std::string_view root_path) : root_path(root_path) {}

void SoundManager::load(const std::string_view key) {
    std::string path = std::string(root_path) + std::string(key);
    Mix_Chunk *ptr = Mix_LoadWAV(path.c_str());

    if (ptr == nullptr) {
        throw std::runtime_error("Failed to load texture");
    }

    SDL_Log("Load texture: %s (addr: %p)", path.c_str(), ptr);
    loaded_sounds.insert(std::make_pair(key, ptr));
}

void SoundManager::unload(const std::string_view key) {
    Mix_Chunk *ptr = this->loaded_sounds.at(key);

    if (ptr == NULL) {
        return;
    }

    Mix_FreeChunk(ptr);
    this->loaded_sounds.erase(key);
}

Mix_Chunk *SoundManager::get(const std::string_view key) const {
    return loaded_sounds.at(key);
}

SoundManager::~SoundManager() {
    for (const auto &[key, ptr] : this->loaded_sounds) {
        Mix_FreeChunk(ptr);
    }
}
