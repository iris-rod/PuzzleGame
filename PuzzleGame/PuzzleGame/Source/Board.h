#pragma once
#include "Object.h"

class Board : public Object {

	Board(const std::string _id, SDL_Rect* _src, SDL_Rect* _dest, const int _sizeX, const int _sizeY);
};