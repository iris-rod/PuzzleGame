#pragma once
#include <vector>
#include "Consts.h"
#include "Ore.h"

class BoardHandler {
public:
	BoardHandler();
	void Init();
	std::vector<Piece*> GetObjs();

private:
	std::vector<Piece*> pieces;
	std::vector<int> mapSize {MAP_SIZE_X, MAP_SIZE_Y};
	
	void GeneratePieces();
	void AddColumn();
	void MoveColumn();
	void UpdateRow();
};
