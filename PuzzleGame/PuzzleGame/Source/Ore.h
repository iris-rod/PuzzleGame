#pragma once
#include "Piece.h"

enum Colors {
	RED,
	GREEN,
	YELLOW,
	BLUE,
	ORANGE
};

class Ore : public Piece {
public:
	Ore(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y);
	//~Ore();

private:
	Colors color;
};