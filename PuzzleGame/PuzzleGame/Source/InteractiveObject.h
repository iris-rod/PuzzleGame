#pragma once
#include "EventHandler.h"
#include "Object.h"
#include <string>
#include <memory>

class InteractiveObject : public Object {
public:
	InteractiveObject() = default;
	InteractiveObject(const std::string _id, SDL_Rect* _src, SDL_Rect* _dest, const int _sizeX, const int _sizeY);
	//void virtual Update();
	//void virtual RegisterEvents(const EventHandler&);
};