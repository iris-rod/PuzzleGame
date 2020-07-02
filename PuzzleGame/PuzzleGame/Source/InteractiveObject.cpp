#include "InteractiveObject.h"
#include "TextureManager.h"

InteractiveObject::InteractiveObject(const std::string _id, SDL_Rect* _src, SDL_Rect* _dest) : Object(_id, _src, _dest) {
	std::cout << "create interactive obj" << std::endl;
}
