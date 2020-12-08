#pragma once
#include "Piece.h"
#include "Utils.h"

using namespace PieceStuff;
using namespace std;

class Ore : public Piece {
public:
	Ore(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y, const int _sizeX, const int _sizeY);
	~Ore();

	const Colors& GetColor() const;

private:
	unique_ptr<Colors> color;
};