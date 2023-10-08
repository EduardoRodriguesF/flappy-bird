#pragma once

#include "SDL2/SDL.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <map>
#include <string>

struct SoundManager {
    SoundManager(std::string_view root_path);
    ~SoundManager();
    void load(const std::string_view key);
    void unload(const std::string_view key);
    Mix_Chunk *get(const std::string_view key) const;

  private:
    std::string_view root_path;
    std::map<const std::string_view, Mix_Chunk*> loaded_sounds;
};
