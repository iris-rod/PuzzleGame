#include "BoardHandler.h"

using namespace std;

BoardHandler::BoardHandler() {
	pieces.resize(mapSize[0] * mapSize[1]);
}

void BoardHandler::GeneratePieces(EventListener& otherHandler) {
	int id = 0;
	for (int c = 0; c < mapSize[0]; c++) { 
		for (int r = 0; r < mapSize[1]; r++) {
			SDL_Rect* src = new SDL_Rect();
			SDL_Rect* dest = new SDL_Rect();
			int co = c * PIECE_SIZE_X + START_X;
			int ro = r * PIECE_SIZE_Y + START_Y;
			if(c >= INITIAL_COLUMNS) pieces[id] = make_shared<Ore>(id, src, dest, co, ro, PIECE_SIZE_X, PIECE_SIZE_Y, true);
			else {
				pieces[id] = make_shared<Ore>(id, src, dest, co, ro, PIECE_SIZE_X, PIECE_SIZE_Y, false);
				pieces[id]->RegisterEvents(otherHandler);
			}
			id++;
		}
	}
}

void BoardHandler::SetPiecesNeighbours(int column = -1) {
	int numElems = pieces.size();
	int init = pieces.size() - 1;
	int end = 0;

	if (column != -1) {
		numElems = pieces.size() / MAP_SIZE_X;
		init = (numElems * column) + numElems - 1;
		end = numElems * column;
	}

	for (int i = init; i >= end; --i) {

		auto piece = pieces[i];
		piece->ClearNeighbours();

		for (int j = -1; j <= 1; j += 2) {
			int newX = piece->GetBoardPosition().x + j;
			int newY = piece->GetBoardPosition().y + j;

			if (newY >= 0 && newY < mapSize[1]) {
				SetNeighbour(*piece.get(), piece->GetBoardPosition().x, newY);
			}
			if (newX >= 0 && newX < mapSize[0]) {
				SetNeighbour(*piece.get(), newX, piece->GetBoardPosition().y);
			}
		}
	}
}

void BoardHandler::SetNeighbour(Piece& piece, const int& x, const int& y) {
	bool canBeRemoved = piece.GetTextureId() == FindPieceFromBoardPosition(x, y)->GetTextureId();
	piece.AddNeighbour(canBeRemoved, x, y, ConvertBoardPositionToDirection(piece.GetBoardPosition().x, piece.GetBoardPosition().y, x, y));
}

std::vector<shared_ptr<Piece>>& BoardHandler::GetObjs() {
	return pieces;
}

void BoardHandler::Init(SDLEventHandler& sdl_handler, EventListener& otherHandler) {
	// init board (basically just an object with a background texture
	GeneratePieces(otherHandler);
	SetPiecesNeighbours();
	RegisterEvents(sdl_handler, otherHandler);
}

void BoardHandler::RegisterEvents(SDLEventHandler& sdl_handler, EventListener& otherHandler) {
	sdl_handler.Subscribe(SDL_MOUSEBUTTONDOWN, [&](SDL_Event const& event) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		Piece* clickedPiece = FindPiece(x, y);

		if (clickedPiece != nullptr) {
			Event* event_p = new EventPieceRemoved(*clickedPiece);
			if (clickedPiece->CanRemove()) {
				otherHandler.NotifyEvent(event_p);
				clickedPiece->Remove(&otherHandler);
			}
		}
	});

	otherHandler.Subscribe(COLUMN_UPDATE, [this](Event const& _event) {
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventColumnUpdate& event_p = dynamic_cast<EventColumnUpdate&>(nonConstEvent);
		OrganiseColumn(event_p.GetColumn());

		if (IsColumnEmpty(event_p.GetColumn())) {
			MoveColumnsBack(event_p.GetColumn());
		}
		SetPiecesNeighbours();
	});
}

Piece* BoardHandler::FindPiece(const int& x, const int& y) const {
	for (auto& piece : pieces) {
		auto coordinates = piece->GetCoordinates();
		if (x >= coordinates.x && x < coordinates.x + PIECE_SIZE_X
			&& y >= coordinates.y && y < coordinates.y + PIECE_SIZE_Y) {
			return piece.get();
		}
	}
	return nullptr;
}

const Piece* BoardHandler::FindPieceFromBoardPosition(const int& x, const int& y) const {
	for (auto& piece : pieces) {
		auto coordinates = piece->GetBoardPosition();
		if (x == coordinates.x && y == coordinates.y) {
			return piece.get();
		}
	}
	return nullptr;
}

bool BoardHandler::IsColumnEmpty(int column) {
	int numElems = pieces.size() / MAP_SIZE_X;
	int init = (numElems * column) + numElems - 1;//get last index of column c
	int end = numElems * column; //get the first index of column c

	for (int i = init; i >= end; --i) {
		auto& p = pieces[i];
		if (!p->IsEmpty()) {
			return false;
		}
	}

	return true;
}

void BoardHandler::MoveColumnsBack(int startColumn) {

	int numElems = pieces.size() / MAP_SIZE_X;

	for (int c = startColumn; c >= 0; --c) {
		int init = (numElems * c) + numElems - 1;//get last index of column c
		int end = numElems * c; //get the first index of column c
		for (int i = init; i >= end; --i) {
			auto& p = pieces[i];
			auto pieceIndex = i - numElems;
			if (pieceIndex < 0) {
				return;
			}
			auto& toSwap = pieces[pieceIndex];
			p->Swap(*toSwap.get());
		}
	}
}

// searches from the last index to the first since the map is
// 0 7 14 21 ...
// 1 8 15 22
// 2 9 16 23 ..
void BoardHandler::OrganiseColumn(int c) {
	int numElems = pieces.size() / MAP_SIZE_X;

	//set initial values for aux variables as the first index to be searched
	int begin = (numElems * c) + numElems - 1;
	int med = (numElems * c) + numElems - 1;

	int init = (numElems * c) + numElems - 1;//get last index of column c
	int end = numElems * c; //get the first index of column c

	for (int i = init; i >= end; --i) {
		auto& p = pieces[i];
		if (!p->IsEmpty()) {
			if (begin != med) {
				pieces[begin].get()->Swap(*pieces[med].get());
			}
			--begin;
		}
		--med;
	}
}