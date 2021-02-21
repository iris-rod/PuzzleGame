#pragma once
#include <string>
#include "SDL.h"
#include <iostream>

using namespace std;

class Object {
public: 
	Object() = default;
	Object(const std::string id, SDL_Rect* src, SDL_Rect* dest, const int x, const int y, const int _sizeX, const int _sizeY);
	~Object();
	const SDL_Rect* GetSrcRect() const;
	const SDL_Rect* GetDestRect() const;
	const std::string& GetTextureId() const;
	virtual SDL_Texture* GetTexture() const;


protected:
	string textureId = "";
	string ID = "";
	SDL_Rect* src = nullptr;
	SDL_Rect* dest = nullptr;
	int sizeX = 0;
	int sizeY = 0;

};