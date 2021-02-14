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
	void OrganiseColumn(int c);
	void MoveColumnsBackFrom(int startColumn);
	void MoveColumnsForward();
	void HandleMoveForward(int startColum, int endColumn);
	void HandleMoveBack(int startColum, int endColumn);
	void SwapColumn(int startIndex, int endIndex);
	void RemoveAllEmptyColumns();
	void ReCalculateCurrentColumns();
	void SetupRegisterEventsOnMostForwardColumn();

	void CreatePieceOnBoard(int c, int r, int index);

	Piece* FindPiece(const int& x, const int& y) const;
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;
};

