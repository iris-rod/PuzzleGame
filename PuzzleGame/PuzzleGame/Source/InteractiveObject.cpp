#include "InteractiveObject.h"
#include "TextureManager.h"

InteractiveObject::InteractiveObject(const std::string _id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY)
	: Object(_id, _src, _dest, x, y, _sizeX, _sizeY), coordinates(nullptr) {
	coordinates = make_unique<Coordinates>(x,y);
}

const Coordinates& InteractiveObject::GetCoordinates() const {
	return *coordinates.get();
}