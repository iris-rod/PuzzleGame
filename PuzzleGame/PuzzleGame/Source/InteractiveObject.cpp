#include "InteractiveObject.h"
#include "TextureManager.h"

InteractiveObject::InteractiveObject(const std::string _id, SDL_Rect* _src, SDL_Rect* _dest, const int _sizeX, const int _sizeY) 
	: Object(_id, _src, _dest, _sizeX, _sizeY) {
	//std::cout << "create interactive obj" << std::endl;
}
