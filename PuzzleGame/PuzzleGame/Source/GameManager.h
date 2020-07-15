#pragma once
#include <memory>
#include <deque>
#include "Ore.h"
#include "RendererObj.h"
#include "TextureManager.h"
#include "BoardHandler.h"

enum GameState {
	OnGoing,
	OnPause,
	Finished
};

class GameManager {
public:
	GameManager() = default;
	//~GameManager();
	void Init(RendererObj* rendererObj);
	//void Update();
	void Render(RendererObj* rendererObj);

private:
	void LoadTextures(RendererObj* rendererObj);

	BoardHandler* boardHandler;
	GameState gameState;
	std::deque<Object*> objs;
};
