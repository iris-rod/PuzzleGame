#include "Ore.h"

Ore::Ore(int Id, int x, int y, const int _sizeX, const int _sizeY, bool empty) 
	: Piece(Id, x, y, _sizeX, _sizeY, empty) {

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

void Ore::GenerateNewTexture() {
	color = make_unique<Colors>(GetRandomColor());
	textureId = ConvertColorToTextureId(*(color.get()));
}

void Ore::Swap(Ore& b) {

	cout << "ore swap" << endl;
	auto color = b.color.get();
	b.color.reset(this->color.get());
	this->color.reset(color);

	Piece::Swap(b);
}
