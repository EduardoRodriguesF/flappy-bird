#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include <map>
#include <string>

struct Texture {
    SDL_Texture *ptr;
    int width;
    int height;
    Texture(SDL_Texture *ptr, int width, int height);
};

struct TextureManager {
    TextureManager(SDL_Renderer *renderer, std::string_view root_path);
    ~TextureManager();
    void load(const std::string_view key, int width, int height);
    void unload(const std::string_view key);
    const Texture *get(const std::string_view key) const;

  private:
    SDL_Renderer *renderer;
    std::string_view root_path;
    std::map<const std::string_view, Texture> loaded_textures;
};
