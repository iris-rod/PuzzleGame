#pragma once
#include <memory>
#include <deque>
#include "Ore.h"
#include "RendererObj.h"
#include "TextureManager.h"
#include "BoardHandler.h"

using namespace std;

enum class GameState {
	ON_GOING,
	ON_PAUSE,
	FINISHED,
	QUIT
};

class GameManager {
public:
	GameManager();
	void Init(RendererObj* rendererObj, SDLEventHandler& handler, EventListener& otherHandler);
	//void Update();
	void Render(RendererObj* rendererObj);
	void Clear();

	bool IsGameOnGoing();
	bool IsGameFinished();
	bool IsGameOnPause();

private:
	void LoadTextures(RendererObj* rendererObj);
	void RegisterEvent(SDLEventHandler& handler);
	void Quit();

	unique_ptr<BoardHandler> boardHandler;
	GameState gameState;
	deque<Object*> objs;
};
