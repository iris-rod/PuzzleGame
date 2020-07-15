#pragma once
#include <string>
#include "SDL.h"
#include <iostream>

class Object {
public: 
	Object() = default;
	Object(const std::string id, SDL_Rect* src, SDL_Rect* dest, const int _sizeX, const int _sizeY);
	//~Object();
	SDL_Rect* GetSrcRect();
	SDL_Rect* GetDestRect();
	std::string GetTextureId();

protected:
	std::string textureId;
	std::string ID;
	SDL_Rect* src;
	SDL_Rect* dest;
	int sizeX;
	int sizeY;

};