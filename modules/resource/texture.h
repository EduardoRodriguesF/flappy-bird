#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include <map>
#include <string>

struct Texture {
    SDL_Texture* ptr;
    int width;
    int height;
    Texture(SDL_Texture* ptr, int width, int height);
    ~Texture();
};

struct TextureManager {
    std::map<const char*, Texture> loaded_textures;

    TextureManager(SDL_Renderer* renderer, std::string root_path);
    void load(const char* key, int width, int height);
    void unload(const char* key);
    const Texture* get(const char* key) const;

private:
    SDL_Renderer *renderer;
    std::string root_path;
};
