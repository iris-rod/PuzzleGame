#pragma once
#include "Object.h"
#include <vector>
#include "Consts.h"
#include "Ore.h"
#include "SDLEventHandler.h"
#include "EventHandler.h"

using namespace std;

class Board {
public:
	Board();

	vector<shared_ptr<Piece>>& GetObjs();
	const vector<int> GetBoardSize() const;
	void CreateAndAddPiece(int c, int r, int index);
	void GeneratePieces(shared_ptr<EventListener>& handler);
	void RegeneratePieces();
	const int GetNumberOfPieces() const;
	const shared_ptr<Piece>& GetPieceByIndex(int i) const;
	void HandlePiecesNeighbours();
	void SwapPiecesOnIndex(int pieceInd, int targetPieceInd);
	bool IsPieceOnIndexEmpty(int ind);

private:

	void SetNeighboursForPiece(shared_ptr<Piece> piece);
	void SetNeighbour(Piece& piece, const int& x, const int& y);
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;

	vector<shared_ptr<Piece>> pieces;
	vector<int> mapSize{ TOTAL_COLUMNS, TOTAL_ROWS };
};