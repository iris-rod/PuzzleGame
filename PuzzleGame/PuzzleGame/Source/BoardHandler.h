#pragma once
#include <vector>
#include "Consts.h"
#include "Ore.h"
#include "SDLEventHandler.h"
#include "EventHandler.h"

class BoardHandler {
public:
	BoardHandler();
	~BoardHandler();
	void Init(SDLEventHandler& sdl_handler, EventListener& other_handler);
	std::vector<Piece*> GetObjs();

private:
	std::vector<Piece*> pieces;
	std::vector<int> mapSize {MAP_SIZE_X, MAP_SIZE_Y};
	
	void GeneratePieces(EventListener& otherHandler);
	void SetPiecesNeighbours();
	void SetNeighbour(Piece* piece, const int& x, const int& y);
	void RegisterEvents(SDLEventHandler& sdl_handler, EventListener& otherHandler);
	Piece* FindPiece(const int& x, const int& y) const;
	const Piece* FindPieceFromBoardPosition(const int& x, const int& y) const;
	void RemovePieces(Piece& piece);
	void AddColumn();
	void MoveColumn();
	void UpdateRow();
};
