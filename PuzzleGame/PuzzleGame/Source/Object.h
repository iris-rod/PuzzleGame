#pragma once
#include <string>
#include "SDL.h"
#include <iostream>

class Object {
public: 
	Object() = default;
	Object(const std::string id, SDL_Rect* src, SDL_Rect* dest, const int _sizeX, const int _sizeY);
	//~Object();
	const SDL_Rect* GetSrcRect() const;
	const SDL_Rect* GetDestRect() const;
	const std::string GetTextureId() const;

protected:
	std::string textureId;
	std::string ID;
	SDL_Rect* src;
	SDL_Rect* dest;
	int sizeX;
	int sizeY;

};