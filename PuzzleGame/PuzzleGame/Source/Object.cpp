#include "Object.h"

Object::Object(const std::string id, SDL_Rect* _src, SDL_Rect* _dest, const int _sizeX, const int _sizeY) 
	: ID(id), src(_src), dest(_dest), sizeX(_sizeX), sizeY(_sizeY) {

	//std::cout << "create object" << std::endl;
}

const SDL_Rect* Object::GetDestRect() const {
	return dest;
}

const SDL_Rect* Object::GetSrcRect() const {
	return src;
}

const std::string Object::GetTextureId() const {
	return textureId;
}