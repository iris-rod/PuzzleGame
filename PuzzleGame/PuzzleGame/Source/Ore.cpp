#include "Ore.h"

Ore::Ore(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y, const int _sizeX, const int _sizeY) 
	: Piece(Id, _src, _dest, x, y, _sizeX, _sizeY) {
	color = GetRandomColor();
	textureId = ConvertColorToTextureId(color);
}

const Colors& Ore::GetColor() const {
	return color;
}

bool Ore::CanRemove() {
	return Piece::CanRemove();
}

void Ore::Remove() {
	Piece::Remove();
	color = Colors::EMPTY;
	textureId = ConvertColorToTextureId(color);
}
