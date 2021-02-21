#include "Board.h"

Board::Board() {
	pieces.resize(mapSize[0] * mapSize[1]);
}

vector<shared_ptr<Piece>>& Board::GetObjs() {
	return pieces;
}

const shared_ptr<Piece>& Board::GetPieceByIndex(int i) const {
	return pieces[i];
}

const vector<int> Board::GetBoardSize() const{
	return mapSize;
}

void Board::RegeneratePieces() {
	int id = 0;
	for (int c = 0; c < mapSize[0]; c++) {
		for (int r = 0; r < mapSize[1]; r++) {
			if (c < TOTAL_COLUMNS - INITIAL_COLUMNS) pieces[id]->MakeEmpty();
			else pieces[id]->GenerateNewColor();
			id++;
		}
	}
}

void Board::GeneratePieces(EventListener& handler) {
	int id = 0;
	for (int c = 0; c < mapSize[0]; c++) {
		for (int r = 0; r < mapSize[1]; r++) {
			CreateAndAddPiece(c, r, id);
			pieces[id]->RegisterEvents(handler);
			id++;	
		}
	}
}

void Board::CreateAndAddPiece(int c, int r, int index) {
	int co = c * PIECE_SIZE_X + START_X;
	int ro = r * PIECE_SIZE_Y + START_Y;

	if (c < TOTAL_COLUMNS - INITIAL_COLUMNS) pieces[index] = make_shared<Piece>(index, co, ro, PIECE_SIZE_X, PIECE_SIZE_Y, true);
	else pieces[index] = make_shared<Piece>(index, co, ro, PIECE_SIZE_X, PIECE_SIZE_Y, false);
}

const int Board::GetNumberOfPieces() const {
	return pieces.size();
}

void Board::HandlePiecesNeighbours() {
	int numElems = pieces.size();
	int init = numElems - 1;
	int end = 0;

	for (int i = init; i >= end; --i) {

		auto piece = pieces[i];
		if (!piece->IsEmpty()) {
			piece->ClearNeighbours();
			SetNeighboursForPiece(piece);
		}
	}
}

void Board::SetNeighboursForPiece(shared_ptr<Piece> piece) {
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

void Board::SetNeighbour(Piece& piece, const int& x, const int& y) {
	auto p = FindPieceFromBoardPosition(x, y);
	if (p != nullptr) {
		bool canBeRemoved = piece.GetTextureId() == p->GetTextureId();
		piece.AddNeighbour(canBeRemoved, x, y, ConvertBoardPositionToDirection(piece.GetBoardPosition().x, piece.GetBoardPosition().y, x, y));
	}
}

const Piece* Board::FindPieceFromBoardPosition(const int& x, const int& y) const {
	for (auto& piece : pieces) {
		auto coordinates = piece->GetBoardPosition();
		if (x == coordinates.x && y == coordinates.y) {
			return piece.get();
		}
	}
	return nullptr;
}

void Board::SwapPiecesOnIndex(int pieceInd, int targetPieceInd) {
	pieces[pieceInd].get()->Swap(*pieces[targetPieceInd].get());
}

bool Board::IsPieceOnIndexEmpty(int ind) {
	return pieces[ind]->IsEmpty();
}