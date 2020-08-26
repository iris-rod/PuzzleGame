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

void BoardHandler::Init(EventHandler& handler) {
	// init board (basically just an object with a background texture
	GeneratePieces();
	RegisterEvents(handler);
}

void BoardHandler::RegisterEvents(EventHandler& handler) {
	handler.Subscribe(SDL_MOUSEBUTTONDOWN, [this](SDL_Event const& event) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		FindPiece(x, y);
	});
}

Piece* BoardHandler::FindPiece(int& x, int& y) {
	for (auto& piece : pieces) {
		auto coordinates = piece->GetPosition();
		if (x >= coordinates[0] && x < coordinates[0] + PIECE_SIZE_X
			&& y >= coordinates[1] && y < coordinates[1] + PIECE_SIZE_Y) {
			std::cout << "on piece: " << piece->GetTextureId() << std::endl;
			return piece;
		}
	}
	return nullptr;
}