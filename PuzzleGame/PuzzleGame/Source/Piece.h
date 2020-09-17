#pragma once
#include "InteractiveObject.h"
#include <vector>
#include <stack>
#include <list>

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

struct NeighbourInfo {
	bool canRemove;
	BoardPosition* position;

	NeighbourInfo(const bool _canRemove, const int _x, const int _y) {
		position = new BoardPosition(_x, _y);
		canRemove = _canRemove;
	}
};

class Piece : public InteractiveObject {
public:
	Piece() = default;
	Piece(const int Id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY);
	//~Piece();
	const BoardPosition* GetBoardPosition() const;
	const Coordinates* GetCoordinates() const;
	const void AddNeighbour(NeighbourInfo* neighbour);

	bool operator==(const Piece& a) {
		return this->boardPosition->x == a.boardPosition->x && this->boardPosition->y == a.boardPosition->y
			&& this->coordinates->x == a.coordinates->x && this->coordinates->y == a.coordinates->y;
	}

	bool CanBeRemoved();

private:
	std::unique_ptr<BoardPosition> boardPosition;
	std::unique_ptr<Coordinates> coordinates;
	std::list<NeighbourInfo*> neighbours;
};