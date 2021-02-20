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
#include "TimeHandler.h"

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

	bool IsGameOnGoing();
	bool IsGameFinished();
	bool IsGameOnPause();
	void Quit();

private:
	void LoadTextures();
	void LoadFonts();
	void ClearObjects();
	void RegisterSDLEvent(SDLEventHandler& handler);
	void RegisterGameEvent(EventListener& handler);

	unique_ptr<BoardHandler> boardHandler;
	unique_ptr<FontsManager> fontsManager;
	unique_ptr<PointSystem> pointSystem;
	shared_ptr<Text> infoText;
	GameState gameState;
	deque<shared_ptr<Object>> objs;
	shared_ptr<RendererObj> rendererObj;

	unique_ptr<TimeHandler> timeHandlerNewColumn;
	unique_ptr<TimeHandler> timeHandlerInfoText;

};
