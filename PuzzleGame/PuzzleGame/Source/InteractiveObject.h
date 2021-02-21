#pragma once
#include "Object.h"
#include <string>
#include <memory>

struct Coordinates {
	int x;
	int y;

	Coordinates(const int _x, const int _y) : x(0), y(0) {
		x = _x;
		y = _y;
	}
};

class InteractiveObject : public Object {
public:
	InteractiveObject() = default;
	InteractiveObject(const std::string _id, const int x, const int y, const int _sizeX, const int _sizeY);


	const Coordinates& GetCoordinates() const;

protected:
	unique_ptr<Coordinates> coordinates;
};