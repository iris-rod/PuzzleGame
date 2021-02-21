#pragma once
#include <string>
#include "SDL.h"
#include <iostream>

using namespace std;

class Object {
public: 
	Object() = default;
	Object(const std::string id, const int x, const int y, const int _sizeX, const int _sizeY);
	~Object();
	const SDL_Rect* GetSrcRect() const;
	const SDL_Rect* GetDestRect() const;
	const std::string& GetTextureId() const;
	virtual SDL_Texture* GetTexture() const;
	void SetTexture(string name);

protected:
	string textureId = "";
	string ID = "";
	unique_ptr<SDL_Rect> src = nullptr;
	unique_ptr<SDL_Rect> dest = nullptr;
	int sizeX = 0;
	int sizeY = 0;

};