#include "Object.h"
#include "TextureManager.h"

Object::Object(const std::string id, const int x, const int y, const int _sizeX, const int _sizeY)
	: ID(id), src(nullptr), dest(nullptr), sizeX(_sizeX), sizeY(_sizeY) {

	src = make_unique<SDL_Rect>();
	dest = make_unique<SDL_Rect>();
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
	return dest.get();
}

const SDL_Rect* Object::GetSrcRect() const {
	return src.get();
}

const std::string& Object::GetTextureId() const {
	return textureId;
}

SDL_Texture* Object::GetTexture() const {
	return TextureManager::GetTexture(textureId);
}