#pragma once
#include <memory>
#include <deque>
#include "Ore.h"
#include "RendererObj.h"
#include "TextureManager.h"
#include "BoardHandler.h"
#include "EventHandler.h"

enum class GameState {
	ON_GOING,
	ON_PAUSE,
	FINISHED,
	QUIT
};

class GameManager {
public:
	GameManager() = default;
	//~GameManager();
	void Init(RendererObj* rendererObj, EventHandler& handler);
	//void Update();
	void Render(RendererObj* rendererObj);

	bool IsGameOnGoing();
	bool IsGameFinished();
	bool IsGameOnPause();

private:
	void LoadTextures(RendererObj* rendererObj);
	void RegisterEvent(EventHandler& handler);
	void Quit();

	BoardHandler* boardHandler;
	GameState gameState;
	std::deque<Object*> objs;
};
