#include "BoardHandler.h"

using namespace std;

BoardHandler::BoardHandler() {
	pieces.resize(mapSize[0] * mapSize[1]);
}

BoardHandler::~BoardHandler() {
	for (int id = 0; id < pieces.size(); id++) {
		pieces[id]->~Piece();
	}
	pieces.clear();
	pieces.resize(0);
}

void BoardHandler::GeneratePieces(EventListener& otherHandler) {
	int id = 0;
	for (int c = 0; c < mapSize[0]; c++) { 
		for (int r = 0; r < mapSize[1]; r++) {
			SDL_Rect* src = new SDL_Rect();
			SDL_Rect* dest = new SDL_Rect();
			pieces[id] = new Ore(id, src, dest, c * PIECE_SIZE_X, r * PIECE_SIZE_Y, PIECE_SIZE_X, PIECE_SIZE_Y);
			pieces[id]->RegisterEvents(otherHandler);
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
	piece->AddNeighbour(new NeighbourInfo(canBeRemoved, x, y, ConvertBoardPositionToDirection(piece->GetBoardPosition()->x, piece->GetBoardPosition()->y, x, y)));
}

std::vector<Piece*> BoardHandler::GetObjs() {
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
			Event* event_p = new EventPieceRemoved(clickedPiece);
			if (clickedPiece->CanRemove()) {
				otherHandler.NotifyEvent(event_p);
				clickedPiece->Remove(&otherHandler);
			}
		}
	});

	otherHandler.Subscribe(COLUMN_UPDATE, [this](Event const& _event) {
		cout << "column update" << endl;
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventColumnUpdate& event_p = dynamic_cast<EventColumnUpdate&>(nonConstEvent);
		cout << event_p.GetColumn() << endl;
		OrganiseColumn(event_p.GetColumn());


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

void BoardHandler::OrganiseColumn(int c) {
	int numElems = pieces.size() / MAP_SIZE_X;
	int begin = (numElems * c) + numElems;
	int med = (numElems * c) + numElems;

	for (int i = (numElems * c) + numElems; i > numElems * c; --i) {
		Piece* p = pieces[i];
		if (!p->IsEmpty()) {
			if (begin != med) {
				cout << "swap: " << begin << ", " << pieces[begin]->GetTextureId() << ", " << med << ", " << pieces[med]->GetTextureId() << endl;
				swap(pieces[begin], pieces[med]);
			}
			--begin;
		}
		--med;
	}

	for (int i = numElems * c; i < (numElems * c) + numElems; ++i) {
		Piece* p = pieces[i];
		cout << p->GetTextureId() << endl;
	}
	cout << endl;
}