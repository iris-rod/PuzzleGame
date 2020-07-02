#pragma once
#include <memory>
#include <deque>
#include "Ore.h"
#include "RendererObj.h"
#include "TextureManager.h"

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
	GameState gameState;
	std::deque<Object*> objs;
};
