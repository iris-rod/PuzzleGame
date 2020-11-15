#pragma once
#include "Piece.h"
#include "Utils.h"

class Ore : public Piece {
public:
	Ore(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y, const int _sizeX, const int _sizeY);
	~Ore();

	const Colors& GetColor() const;

	//bool CanRemove();
	//void Remove();

private:
	Colors color;
};