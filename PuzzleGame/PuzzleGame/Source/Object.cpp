#include "Object.h"

Object::Object(const std::string id, SDL_Rect* _src, SDL_Rect* _dest) : ID(id), src(_src), dest(_dest) {

	std::cout << "create object" << std::endl;
}

SDL_Rect* Object::GetDestRect() {
	return dest;
}

SDL_Rect* Object::GetSrcRect() {
	return src;
}

std::string Object::GetTextureId() {
	return textureId;
}