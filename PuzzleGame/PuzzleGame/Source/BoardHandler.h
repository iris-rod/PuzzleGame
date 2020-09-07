#pragma once
#include <vector>
#include "Consts.h"
#include "Ore.h"

class BoardHandler {
public:
	BoardHandler();
	void Init(EventHandler& handler);
	std::vector<Piece*> GetObjs();

private:
	std::vector<Piece*> pieces;
	std::vector<int> mapSize {MAP_SIZE_X, MAP_SIZE_Y};
	
	void GeneratePieces();
	void SetPiecesNeighbours();
	void RegisterEvents(EventHandler& handler);
	Piece* FindPiece(const int& x, const int& y) const;
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;
	void RemovePieces(Piece& piece);
	void AddColumn();
	void MoveColumn();
	void UpdateRow();
};
