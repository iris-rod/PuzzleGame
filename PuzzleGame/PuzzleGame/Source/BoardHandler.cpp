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
			if(c < TOTAL_COLUMNS - INITIAL_COLUMNS) pieces[id] = make_shared<Piece>(id, src, dest, co, ro, PIECE_SIZE_X, PIECE_SIZE_Y, true);
			else {
				pieces[id] = make_shared<Piece>(id, src, dest, co, ro, PIECE_SIZE_X, PIECE_SIZE_Y, false);
			}
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
		numElems = pieces.size() / TOTAL_COLUMNS;
		init = (numElems * column) + numElems - 1;
		end = numElems * column;
	}

	for (int i = init; i >= end; --i) {

		auto piece = pieces[i];
		if (!piece->IsEmpty()) {
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
}

void BoardHandler::SetNeighbour(Piece& piece, const int& x, const int& y) {
	auto p = FindPieceFromBoardPosition(x, y);
	if (p != nullptr) {
		bool canBeRemoved = piece.GetTextureId() == p->GetTextureId();
		piece.AddNeighbour(canBeRemoved, x, y, ConvertBoardPositionToDirection(piece.GetBoardPosition().x, piece.GetBoardPosition().y, x, y));
	}
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

		if (clickedPiece != nullptr && !clickedPiece->IsEmpty()) {
			Event* event_p = new EventPieceRemoved(*clickedPiece);
			if (clickedPiece->CanRemove()) {
				otherHandler.NotifyEvent(event_p);
				clickedPiece->Remove(&otherHandler);
			}
		}
	});

	otherHandler.Subscribe(COLUMN_UPDATE, [&](Event const& _event) {
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventColumnUpdate& event_p = dynamic_cast<EventColumnUpdate&>(nonConstEvent);
		OrganiseColumn(event_p.GetColumn());
		if (IsColumnEmpty(event_p.GetColumn())) {
			Event* event_empty = new EventEmptyColumn(event_p.GetColumn());
			otherHandler.NotifyEvent(event_empty);
		}
		SetPiecesNeighbours();
	});

	otherHandler.Subscribe(EMPTY_COLUMN, [&](Event const& _event) {
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventEmptyColumn& event_p = dynamic_cast<EventEmptyColumn&>(nonConstEvent);
		MoveColumnsBackFrom(event_p.GetColumn());
		ReCalculateCurrentColumns();
		RemoveAllEmptyColumns();
		SetPiecesNeighbours();
	});
}

inline void BoardHandler::ReCalculateCurrentColumns()
{
	auto a = find_if(pieces.begin(), pieces.end(), [](shared_ptr<Piece>& arg) {
		return arg.get()->GetTextureId() != "empty";
	});
	if (a != pieces.end()) {
		auto b = a->get()->GetBoardPosition().x;
		currentColumns = mapSize[0] - b;
	}
}

void BoardHandler::RemoveAllEmptyColumns() {
	auto numberOfColumns = currentColumns;
	for (int c = mapSize[0] - currentColumns; c < mapSize[0]; c++) {
		if (IsColumnEmpty(c)) {
			MoveColumnsBackFrom(c);
		}
	}
	ReCalculateCurrentColumns();
}

void BoardHandler::ResetNeighbours(int c) {
	SetPiecesNeighbours(c);
	if (c > 0)
		SetPiecesNeighbours(c - 1);
	if (c < TOTAL_ROWS - 1)
		SetPiecesNeighbours(c + 1);
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
	int numElems = pieces.size() / TOTAL_COLUMNS;
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

void BoardHandler::AddColumn(EventListener& otherHandler) {
	MoveColumnsForward();

	if (currentColumns < TOTAL_COLUMNS) {
		int id = pieces.size() - mapSize[1];
		for (int r = 0; r < mapSize[1]; r++) {
			pieces[id].get()->GenerateNewColor();
			id++;
		}
		++currentColumns;
	}

	SetPiecesNeighbours();
}

void BoardHandler::SetupRegisterEventsOnMostForwardColumn() {
}

void BoardHandler::MoveColumnsBackFrom(int startColumn) {
	int endIndex = TOTAL_COLUMNS - currentColumns;
	int startIndex = startColumn;
	HandleMoveBack(startColumn, endIndex);
}

void BoardHandler::MoveColumnsForward() {
	int startIndex = TOTAL_COLUMNS - currentColumns;
	int endIndex = TOTAL_COLUMNS;
	HandleMoveForward(startIndex, endIndex);
}

void BoardHandler::HandleMoveBack(int startColumn, int endColumn) {
	for (int c = startColumn; c >= endColumn; --c) {
		int init = (TOTAL_ROWS * c) + TOTAL_ROWS - 1;//get last index of column c
		int end = TOTAL_ROWS * c; //get the first index of column c
		SwapColumn(init, end);
	}
}

void BoardHandler::HandleMoveForward(int startColumn, int endColumn) {
	for (int c = startColumn; c < endColumn; ++c) {
		int init = (TOTAL_ROWS * c) + TOTAL_ROWS - 1;//get last index of column c
		int end = TOTAL_ROWS * c; //get the first index of column c
		SwapColumn(init, end);
	}
}

void BoardHandler::SwapColumn(int startIndex, int endIndex) {
	for (int i = startIndex; i >= endIndex; --i) {
		auto& p = pieces[i];
		auto pieceIndex = i - TOTAL_ROWS;
		if (pieceIndex < 0) {
			return;
		}
		auto& toSwap = pieces[pieceIndex];
		pieces[i].get()->Swap(*pieces[pieceIndex].get());
	}
}

// searches from the last index to the first since the map is
// 0 7 14 21 ...
// 1 8 15 22
// 2 9 16 23 ..
void BoardHandler::OrganiseColumn(int c) {

	//set initial values for aux variables as the first index to be searched
	int begin = (TOTAL_ROWS * c) + TOTAL_ROWS - 1;
	int med = (TOTAL_ROWS * c) + TOTAL_ROWS - 1;

	int init = (TOTAL_ROWS * c) + TOTAL_ROWS - 1;//get last index of column c
	int end = TOTAL_ROWS * c; //get the first index of column c

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