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

struct NeighboursInfo {
	bool canRemove;
	BoardPosition* position;

	NeighboursInfo(const bool _canRemove, const int _x, const int _y) {
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
	void SetNeighbours(const int& boardWidth, const int& boardHeight, const std::vector<Piece*> pieces);

private:
	std::unique_ptr<BoardPosition> boardPosition;
	std::unique_ptr<Coordinates> coordinates;
	std::list<NeighboursInfo*> neighbours;
	bool canRemove = false;

	void CanBeRemoved();
};