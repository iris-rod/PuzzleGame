#include "BoardHandler.h"

BoardHandler::BoardHandler() {
	pieces.resize(mapSize[0] * mapSize[1]);
	/*for (int i = 0; i < mapSize[0]; i++) {
		pieces.resize(mapSize[1]);
	}*/
}

void BoardHandler::GeneratePieces() {
	int id = 0;
	for (int c = 0; c < mapSize[0]; c++) {
		for (int r = 0; r < mapSize[1]; r++) {
			SDL_Rect* src = new SDL_Rect();
			SDL_Rect* dest = new SDL_Rect();
			pieces[id] = new Ore(id, src, dest, c * PIECE_SIZE_X, r * PIECE_SIZE_Y, PIECE_SIZE_X, PIECE_SIZE_Y);
			id++;
		}
	}
}

std::vector<Piece*> BoardHandler::GetObjs() {
	return pieces;
}

void BoardHandler::Init() {
	// init board (basically just an object with a background texture
	GeneratePieces();
}