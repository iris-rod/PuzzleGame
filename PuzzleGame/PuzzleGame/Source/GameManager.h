#pragma once
#include <memory>
#include <deque>
#include "Ore.h"
#include "RendererObj.h"
#include "TextureManager.h"
#include "BoardHandler.h"
#include "Text.h"
#include "FontsManager.h"
#include "PointSystem.h"

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
	void Init(shared_ptr<RendererObj>& rendererObj, SDLEventHandler& handler, EventListener& otherHandler);
	void Render();
	void HandleTimeTriggeredEvents(EventListener& otherHandler);
	void Clear();

	bool IsGameOnGoing();
	bool IsGameFinished();
	bool IsGameOnPause();
	void Quit();

private:
	void LoadTextures();
	void LoadFonts();
	void RegisterSDLEvent(SDLEventHandler& handler);
	void RegisterGameEvent(EventListener& handler);

	unique_ptr<BoardHandler> boardHandler;
	unique_ptr<FontsManager> fontsManager;
	unique_ptr<PointSystem> pointSystem;
	GameState gameState;
	deque<shared_ptr<Object>> objs;
	shared_ptr<RendererObj> rendererObj;
};
