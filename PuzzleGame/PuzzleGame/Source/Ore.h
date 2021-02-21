#pragma once
#include "Piece.h"
#include "Utils.h"

using namespace PieceStuff;
using namespace std;

class Ore : public Piece {
public:
	Ore(int Id, int x, int y, const int _sizeX, const int _sizeY, bool empty);
	~Ore();

	const Colors& GetColor() const;
	void GenerateNewTexture();
	void Swap(Ore& b);

private:
	unique_ptr<Colors> color;
};