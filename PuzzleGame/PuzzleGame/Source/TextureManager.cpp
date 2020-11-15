#include "TextureManager.h"
#include "SDL_image.h"
#include <iostream>

std::map<std::string, SDL_Texture*> TextureManager::loadedTextures;

void TextureManager::LoadTexture(std::string textureId, SDL_Renderer* renderer, const char* texture_path) {
	if (loadedTextures.find(textureId) != loadedTextures.end()) {
		throw "The texture with this texture ID already exists.";
	}

	SDL_Surface* tempSurface = IMG_Load(texture_path);
	if (tempSurface == nullptr) printf("%s", SDL_GetError());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	loadedTextures[textureId] = tex;
}

SDL_Texture* TextureManager::GetTexture(std::string textureId) {
	return loadedTextures[textureId];
}

void TextureManager::Clean() {
	loadedTextures.clear();
}
