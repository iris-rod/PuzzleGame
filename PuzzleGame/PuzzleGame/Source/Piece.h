#pragma once
#include "InteractiveObject.h"
#include <vector>
#include <stack>

class Piece : public InteractiveObject {
public:
	Piece() = default;
	Piece(const int Id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY);
	//~Piece();
	std::vector<int> GetPosition();
private:
	std::vector<int> position;
	std::stack<Piece*> neighbours;
};