#pragma once
#include "InteractiveObject.h"
#include <vector>
#include <stack>

struct BoardPosition {
	int x;
	int y;

	BoardPosition(const int _x, const int _y) {
		x = _x;
		y = _y;
	}
};

struct Coordinates {
	int x;
	int y;

	Coordinates(const int _x, const int _y) {
		x = _x;
		y = _y;
	}
};

class Piece : public InteractiveObject {
public:
	Piece() = default;
	Piece(const int Id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY);
	//~Piece();
	BoardPosition* GetBoardPosition();
	Coordinates* GetCoordinates();
private:
	BoardPosition* boardPosition;
	Coordinates* coordinates;
	std::stack<BoardPosition*> neighbours;
	bool canRemove = false;

	void SetNeighbours();
	void CanBeRemoved();
};