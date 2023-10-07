#include "texture.h"
#include "SDL2/SDL_log.h"
#include "SDL2/SDL_render.h"
#include "SDL2_image/SDL_image.h"
#include <iostream>
#include <stdexcept>

Texture::Texture(SDL_Texture *ptr, int width, int height)
    : ptr(ptr), width(width), height(height) {}

TextureManager::TextureManager(SDL_Renderer *renderer,
                               std::string_view root_path)
    : renderer(renderer), root_path(root_path) {}

void TextureManager::load(const std::string_view key, int width, int height) {
    std::string path = std::string(root_path) + std::string(key);
    SDL_Texture *ptr = IMG_LoadTexture(renderer, path.c_str());

    SDL_Log("Load texture: %s (w: %i, h: %i, addr: %p)", path.c_str(), width,
            height, ptr);

    if (ptr == nullptr) {
        throw std::runtime_error("Failed to load texture");
    }

    Texture texture = Texture(ptr, width, height);
    loaded_textures.insert(std::make_pair(key, std::move(texture)));
}

void TextureManager::unload(const std::string_view key) {
    this->loaded_textures.erase(key);
}

const Texture *TextureManager::get(const std::string_view key) const {
    return &loaded_textures.at(key);
}

TextureManager::~TextureManager() {
    for (const auto &[key, texture] : this->loaded_textures) {
        SDL_DestroyTexture(texture.ptr);
    }
}
