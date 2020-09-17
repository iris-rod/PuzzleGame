#include "Piece.h"

Piece::Piece(const int id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY) 
	: coordinates( new Coordinates(x, y) ), 
	boardPosition( new BoardPosition(x == 0 ? 0 : x/_sizeX, y == 0 ? 0 : y/_sizeY) ), 
	InteractiveObject("piece" + id, _src, _dest, _sizeX, _sizeY) {
	std::cout << (x == 0 ? 0 : x / _sizeX) << ", " << (y == 0 ? 0 : y / _sizeY) << std::endl;
	src->x = 0;
	src->y = 0;
	dest->x = x;
	dest->y = y;
	src->w = _sizeX;
	src->h = _sizeY;
	dest->w = _sizeX;
	dest->h = _sizeY;
}

const BoardPosition* Piece::GetBoardPosition() const {
	return boardPosition.get();
}

const Coordinates* Piece::GetCoordinates() const {
	return coordinates.get();
}

const void Piece::AddNeighbour(NeighbourInfo* neighbour) {
	neighbours.push_front(neighbour);
}


