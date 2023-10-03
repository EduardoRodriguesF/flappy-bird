#include "texture.h"
#include "SDL2/SDL_render.h"
#include "SDL2_image/SDL_image.h"

Texture::Texture(SDL_Texture* ptr, int width, int height) : ptr(ptr), width(width), height(height) {}

Texture::~Texture() {
    SDL_DestroyTexture(this->ptr);
}

TextureManager::TextureManager(SDL_Renderer* renderer, std::string root_path) : renderer(renderer), root_path(root_path) {}

void TextureManager::load(const char* key, int width, int height) {
    SDL_Texture* ptr = IMG_LoadTexture(renderer, (root_path + key).c_str());

    if (ptr != nullptr) {
        Texture texture = Texture(ptr, width, height);
        loaded_textures.insert(std::make_pair(key, texture));
    }
}

void TextureManager::unload(const char* key) {
    this->loaded_textures.erase(key);
}

const Texture* TextureManager::get(const char* key) const {
    return &loaded_textures.at(key);
}
