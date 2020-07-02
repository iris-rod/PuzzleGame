#pragma once
#include "InteractiveObject.h"
#include <vector>
#include <stack>

class Piece : public InteractiveObject {
public:
	Piece() = default;
	Piece(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y);
	//~Piece();

private:
	std::vector<int> position;
	std::stack<Piece*> neighbours;
};