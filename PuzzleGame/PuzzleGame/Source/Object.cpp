#include "Object.h"
#include "TextureManager.h"

Object::Object(const std::string id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY)
	: ID(id), src(_src), dest(_dest), sizeX(_sizeX), sizeY(_sizeY) {
	//std::cout << "create object" << std::endl;

	src->x = 0;
	src->y = 0;
	dest->x = x;
	dest->y = y;
	src->w = _sizeX;
	src->h = _sizeY;
	dest->w = _sizeX;
	dest->h = _sizeY;
}

Object::~Object() {
	src = nullptr;
	dest = nullptr;
	textureId = "";
	sizeX = 0;
	sizeY = 0;
	ID = "";
}

const SDL_Rect* Object::GetDestRect() const {
	return dest;
}

const SDL_Rect* Object::GetSrcRect() const {
	return src;
}

const std::string& Object::GetTextureId() const {
	return textureId;
}

SDL_Texture* Object::GetTexture() const {
	return TextureManager::GetTexture(textureId);
}