#pragma once
#include <vector>
#include "Consts.h"
#include "Ore.h"
#include "SDLEventHandler.h"
#include "EventHandler.h"

using namespace PieceStuff;

class BoardHandler {
public:
	BoardHandler();
	void Init(SDLEventHandler& sdl_handler, EventListener& other_handler);
	std::vector<shared_ptr<Piece>>& GetObjs();
	void AddColumn(EventListener& otherHandler);

private:
	std::vector<shared_ptr<Piece>> pieces;
	std::vector<int> mapSize { TOTAL_COLUMNS, TOTAL_ROWS};
	int currentColumns = INITIAL_COLUMNS;
	
	void GeneratePieces(EventListener& otherHandler);
	void SetPiecesNeighbours(int column);
	void SetNeighbour(Piece& piece, const int& x, const int& y);
	void RegisterEvents(SDLEventHandler& sdl_handler, EventListener& otherHandler);
	bool IsColumnEmpty(int column);
	void MoveColumnsBack(int startColumn);
	Piece* FindPiece(const int& x, const int& y) const;
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;
	void AddColumn();
	void MoveColumn();
	void OrganiseColumn(int c);
};
