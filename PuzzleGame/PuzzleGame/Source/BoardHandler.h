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
	void ResetNeighbours(int column);
	void SetNeighbour(Piece& piece, const int& x, const int& y);
	void RegisterEvents(SDLEventHandler& sdl_handler, EventListener& otherHandler);
	bool IsColumnEmpty(int column);
	void MoveColumns(int startColumn, bool back);
	void SwapColumn(int startIndex, int endIndex);
	void HandleMoveForward(int startColum, int endColumn);
	void HandleMoveBack(int startColum, int endColumn);
	Piece* FindPiece(const int& x, const int& y) const;
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;
	void OrganiseColumn(int c);
};
