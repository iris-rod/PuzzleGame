#include "Piece.h"

Piece::Piece(int id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y) : position({ x,y }), InteractiveObject("piece" + id, _src, _dest) {
	src->x = x;
	src->y = y;
	dest->x = x;
	dest->y = y;
	std::cout <<"src->x : " << src->x << std::endl;
	std::cout << "src->y : " << src->y << std::endl;
	std::cout << "dest->x : " << dest->x << std::endl;
	std::cout << "dest->y : " << dest->y << std::endl;
	std::cout << "create piece" << std::endl;
}


