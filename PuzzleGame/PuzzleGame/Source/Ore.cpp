#include "Ore.h"

Ore::Ore(int Id, SDL_Rect* _src, SDL_Rect* _dest, int x, int y, const int _sizeX, const int _sizeY) 
	: Piece(Id, _src, _dest, x, y, _sizeX, _sizeY) {
	color = GetRandomColor();
	textureId = ConvertColorToTextureId(color);
	//std::cout << "src->x : " << src->x << std::endl;
	//std::cout << "src->y : " << src->y << std::endl;
	//std::cout << "dest->x : " << dest->x << std::endl;
	//std::cout << "dest->y : " << dest->y << std::endl;
	//std::cout << "create ore" << std::endl;

}
