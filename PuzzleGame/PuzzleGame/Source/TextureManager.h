#pragma once
#include "SDL.h"
#include <map>
#include <string>
#include <memory>

using namespace std;

void SDL_DestroyTexture(SDL_Texture*);

class TextureManager {
public:
	static void LoadTexture(string textureId, SDL_Renderer* renderer, const char* texture_path);
	static SDL_Texture* GetTexture(string textureId);
	static void Clean();

private:
	static map<string, shared_ptr<SDL_Texture>> loadedTextures;
};