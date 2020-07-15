#pragma once
#include "SDL.h"
#include <map>
#include <string>
#include <memory>

class TextureManager {
public:
	static void LoadTexture(std::string textureId, SDL_Renderer* renderer, const char* texture_path);
	static SDL_Texture* GetTexture(std::string textureId);

private:
	static std::map<std::string, SDL_Texture*> loadedTextures;
};