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

private:
	std::vector<shared_ptr<Piece>> pieces;
	std::vector<int> mapSize {MAP_SIZE_X, MAP_SIZE_Y};
	
	void GeneratePieces(EventListener& otherHandler);
	void SetPiecesNeighbours();
	void SetNeighbour(Piece& piece, const int& x, const int& y);
	void RegisterEvents(SDLEventHandler& sdl_handler, EventListener& otherHandler);
	Piece* FindPiece(const int& x, const int& y) const;
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;
	void AddColumn();
	void MoveColumn();
	void OrganiseColumn(int c);
};
