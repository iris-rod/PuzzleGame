#include "TextureManager.h"
#include "SDL_image.h"
#include <iostream>

std::map<std::string, SDL_Texture*> TextureManager::loadedTextures;

void TextureManager::LoadTexture(std::string textureId, SDL_Renderer* renderer, const char* texture_path) {
	std::cout << "LoadTexture" << std::endl;
	if (loadedTextures.find(textureId) != loadedTextures.end()) {
		throw "The texture with this texture ID already exists.";
	}

	SDL_Surface* tempSurface = IMG_Load(texture_path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	loadedTextures[textureId] = tex;
	std::cout << "LoadTexture2 " << tex << std::endl;
}

SDL_Texture* TextureManager::GetTexture(std::string textureId) {
	return loadedTextures[textureId];
}
