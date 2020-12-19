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
			pieces[id] = make_shared<Ore>(id, src, dest, c * PIECE_SIZE_X, r * PIECE_SIZE_Y, PIECE_SIZE_X, PIECE_SIZE_Y);
			pieces[id]->RegisterEvents(otherHandler);
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
		int c = event_p.GetColumn();
		SetPiecesNeighbours(c);
		if(c > 0)
			SetPiecesNeighbours(c - 1);
		if(c < MAP_SIZE_Y - 1)
			SetPiecesNeighbours(c + 1);
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

void BoardHandler::OrganiseColumn(int c) {
	int numElems = pieces.size() / MAP_SIZE_X;
	int begin = (numElems * c) + numElems - 1;
	int med = (numElems * c) + numElems - 1;

	int init = (numElems * c) + numElems - 1;
	int end = numElems * c;

	for (int i = init; i >= end; --i) {
		auto& p = pieces[i];
		if (!p->IsEmpty()) {
			if (begin != med) {
				cout << "swap: " << begin << ", " << pieces[begin]->GetTextureId() << ", " << med << ", " << pieces[med]->GetTextureId() << endl;
				//swap(pieces[begin], pieces[med]);
				
				//pieces[begin].swap(pieces[med]);
				pieces[begin].get()->Swap(*pieces[med].get());
			}
			--begin;
		}
		--med;
	}

	cout << "new collumn " << endl;
	for (int i = end; i <= init; ++i) {
		auto& p = pieces[i];
		cout << p->GetTextureId() << endl;
	}
	cout << endl;
}