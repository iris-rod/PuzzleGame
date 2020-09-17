#include "BoardHandler.h"

BoardHandler::BoardHandler() {
	pieces.resize(mapSize[0] * mapSize[1]);
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

void BoardHandler::SetPiecesNeighbours() {
	for (auto& piece : pieces) {
		for (int i = -1; i <= 1; i += 2) {
			int newX = piece->GetBoardPosition()->x + i;
			int newY = piece->GetBoardPosition()->y + i;

			if (newY >= 0 && newY < mapSize[1]) {
				SetNeighbour(piece, piece->GetBoardPosition()->x, newY);
			}
			if (newX >= 0 && newX < mapSize[0]) {
				SetNeighbour(piece, newX, piece->GetBoardPosition()->y);
			}
		}
	}
}

void BoardHandler::SetNeighbour(Piece* piece, const int& x, const int& y) {
	bool canBeRemoved = piece->GetTextureId() == FindPieceFromBoardPosition(x, y)->GetTextureId();
	piece->AddNeighbour(new NeighbourInfo(canBeRemoved, x, y));
}

std::vector<Piece*> BoardHandler::GetObjs() {
	return pieces;
}

void BoardHandler::Init(EventHandler& handler) {
	// init board (basically just an object with a background texture
	GeneratePieces();
	SetPiecesNeighbours();
	RegisterEvents(handler);
}

void BoardHandler::RegisterEvents(EventHandler& handler) {
	handler.Subscribe(SDL_MOUSEBUTTONDOWN, [this](SDL_Event const& event) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		Piece* clickedPiece = FindPiece(x, y);
	});
}

Piece* BoardHandler::FindPiece(const int& x, const int& y) const {
	for (auto& piece : pieces) {
		auto coordinates = piece->GetCoordinates();
		if (x >= coordinates->x && x < coordinates->x + PIECE_SIZE_X
			&& y >= coordinates->y && y < coordinates->y + PIECE_SIZE_Y) {
			return piece;
		}
	}
	return nullptr;
}

const Piece* BoardHandler::FindPieceFromBoardPosition(const int& x, const int& y) const {
	for (auto& piece : pieces) {
		auto coordinates = piece->GetBoardPosition();
		if (x == coordinates->x && y == coordinates->y) {
			return piece;
		}
	}
	return nullptr;
}