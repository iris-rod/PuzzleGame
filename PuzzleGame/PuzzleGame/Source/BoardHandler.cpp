#include "BoardHandler.h"

using namespace std;

BoardHandler::BoardHandler() {
}

void BoardHandler::Restart() {
	currentColumns = INITIAL_COLUMNS;
	board->RegeneratePieces();
	board->HandlePiecesNeighbours();
}

const vector<shared_ptr<Piece>>& BoardHandler::GetObjs() const {
	return board->GetObjs();
}

void BoardHandler::Init(shared_ptr<SDLEventHandler>& sdl_handler, shared_ptr<EventListener>& otherHandler) {
	board = make_unique<Board>();
	board->GeneratePieces(otherHandler);
	board->HandlePiecesNeighbours();
	RegisterEvents(sdl_handler, otherHandler);
}

void BoardHandler::RegisterEvents(shared_ptr<SDLEventHandler>& sdl_handler, shared_ptr<EventListener>& otherHandler) {
	sdl_handler->Subscribe(SDL_MOUSEBUTTONDOWN, [&](SDL_Event const& event) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		Piece* clickedPiece = FindPiece(x, y);

		if (clickedPiece != nullptr && !clickedPiece->IsEmpty()) {
			Event* event_p = new EventPieceRemoved(*clickedPiece);
			if (clickedPiece->CanRemove()) {
				otherHandler->NotifyEvent(event_p);
				clickedPiece->Remove(otherHandler);
			}
		}
	});

	otherHandler->Subscribe(COLUMN_UPDATE, [&](Event const& _event) {
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventColumnUpdate& event_p = dynamic_cast<EventColumnUpdate&>(nonConstEvent);
		OrganiseColumn(event_p.GetColumn());
		if (IsColumnEmpty(event_p.GetColumn())) {
			Event* event_empty = new EventEmptyColumn(event_p.GetColumn());
			otherHandler->NotifyEvent(event_empty);
		}
		board->HandlePiecesNeighbours();
	});

	otherHandler->Subscribe(EMPTY_COLUMN, [&](Event const& _event) {
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventEmptyColumn& event_p = dynamic_cast<EventEmptyColumn&>(nonConstEvent);
		MoveColumnsBackFrom(event_p.GetColumn());
		ReCalculateCurrentColumns();
		RemoveAllEmptyColumns();
		board->HandlePiecesNeighbours();
	});
}

inline void BoardHandler::ReCalculateCurrentColumns()
{
	auto pieces = board->GetObjs();
	auto a = find_if(pieces.begin(), pieces.end(), [](shared_ptr<Piece>& arg) {
		return arg.get()->GetTextureId() != "empty";
	});
	if (a != pieces.end()) {
		auto boardSize = board->GetBoardSize();
		auto b = a->get()->GetBoardPosition().x;
		currentColumns = boardSize[0] - b;
	}
}

void BoardHandler::RemoveAllEmptyColumns() {
	auto numberOfColumns = currentColumns;
	auto boardSize = board->GetBoardSize();
	for (int c = boardSize[0] - currentColumns; c < boardSize[0]; c++) {
		if (IsColumnEmpty(c)) {
			MoveColumnsBackFrom(c);
		}
	}
	ReCalculateCurrentColumns();
}


Piece* BoardHandler::FindPiece(const int& x, const int& y) const {
	for (auto& piece : board->GetObjs()) {
		auto coordinates = piece->GetCoordinates();
		if (x >= coordinates.x && x < coordinates.x + PIECE_SIZE_X
			&& y >= coordinates.y && y < coordinates.y + PIECE_SIZE_Y) {
			return piece.get();
		}
	}
	return nullptr;
}

bool BoardHandler::IsColumnEmpty(int column) {
	int numElems = board->GetNumberOfPieces() / TOTAL_COLUMNS;
	int init = (numElems * column) + numElems - 1;//get last index of column c
	int end = numElems * column; //get the first index of column c

	for (int i = init; i >= end; --i) {
		if (!board->IsPieceOnIndexEmpty(i)) {
			return false;
		}
	}

	return true;
}

void BoardHandler::AddColumn() {
	MoveColumnsForward();

	if (currentColumns < TOTAL_COLUMNS) {
		auto boardSize = board->GetBoardSize();
		int id = board->GetNumberOfPieces() - boardSize[1];
		for (int r = 0; r < boardSize[1]; r++) {
			board->GetPieceByIndex(id)->GenerateNewColor();
			id++;
		}
		++currentColumns;
	}
	board->HandlePiecesNeighbours();
}

void BoardHandler::HandleAddedNewColumn(shared_ptr<EventListener>& handler) {
	if (currentColumns == TOTAL_COLUMNS)
		handler->NotifyEvent(new Event(END_GAME));
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
		auto pieceIndex = i - TOTAL_ROWS;
		if (pieceIndex < 0) {
			return;
		}
		board->SwapPiecesOnIndex(i, pieceIndex);
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
		if (!board->IsPieceOnIndexEmpty(i)) {
			if (begin != med) {
				board->SwapPiecesOnIndex(begin, med);
			}
			--begin;
		}
		--med;
	}
}
