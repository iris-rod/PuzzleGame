#pragma once
#include "Board.h"

using namespace PieceStuff;

class BoardHandler {
public:
	BoardHandler();
	void Init(SDLEventHandler& sdl_handler, EventListener& other_handler);
	void AddColumn();
	void Restart();
	void HandleAddedNewColumn(EventListener& handler);
	const vector<shared_ptr<Piece>>& GetObjs() const;

private:
	unique_ptr<Board> board;
	int currentColumns = INITIAL_COLUMNS;

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

	Piece* FindPiece(const int& x, const int& y) const;
};

