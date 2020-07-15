#include "Piece.h"

Piece::Piece(const int id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY) 
	: position({ x,y }), InteractiveObject("piece" + id, _src, _dest, _sizeX, _sizeY) {
	src->x = x;
	src->y = y;
	dest->x = x;
	dest->y = y;
	src->w = _sizeX;
	src->h = _sizeY;
	dest->w = _sizeX;
	dest->h = _sizeY;
	//std::cout <<"src->x : " << src->x << std::endl;
	//std::cout << "src->y : " << src->y << std::endl;
	//std::cout << "dest->x : " << dest->x << std::endl;
	//std::cout << "dest->y : " << dest->y << std::endl;
	//std::cout << "create piece" << std::endl;
}


