#include "TextureManager.h"
#include "SDL_image.h"
#include <iostream>

map<string, shared_ptr<SDL_Texture>> TextureManager::loadedTextures;

void TextureManager::LoadTexture(string textureId, SDL_Renderer* renderer, const char* texture_path) {
	if (loadedTextures.find(textureId) != loadedTextures.end()) {
		throw "The texture with this texture ID already exists.";
	}

	SDL_Surface* tempSurface = IMG_Load(texture_path);

	if (tempSurface == nullptr) {
		printf("%s", SDL_GetError());
		return;
	}

	unique_ptr< SDL_Texture, decltype(&SDL_DestroyTexture)> text = { SDL_CreateTextureFromSurface(renderer, tempSurface), &SDL_DestroyTexture };
	loadedTextures.try_emplace(textureId, move(text));

	SDL_FreeSurface(tempSurface);
}

SDL_Texture* TextureManager::GetTexture(string textureId) {
	return loadedTextures[textureId].get();
}

void TextureManager::Clean() {
	loadedTextures.clear();
}
