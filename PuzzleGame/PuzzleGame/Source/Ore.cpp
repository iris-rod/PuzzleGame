#include "Ore.h"

Ore::Ore(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y, const int _sizeX, const int _sizeY, bool empty) 
	: Piece(Id, _src, _dest, x, y, _sizeX, _sizeY) {

	if (empty)	color = make_unique<Colors>(Colors::EMPTY);
	else color = make_unique<Colors>(GetRandomColor());

	textureId = ConvertColorToTextureId(*(color.get()));
}

Ore::~Ore() {
	color = make_unique<Colors>(Colors::EMPTY);
}

const Colors& Ore::GetColor() const {
	return *(color.get());
}
