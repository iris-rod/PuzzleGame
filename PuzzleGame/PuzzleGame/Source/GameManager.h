#pragma once
#include <memory>
#include <deque>
#include "Ore.h"
#include "RendererObj.h"
#include "TextureManager.h"
#include "BoardHandler.h"
#include "Text.h"
#include "FontsManager.h"

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
	void Render(RendererObj* rendererObj);
	void HandleTimeTriggeredEvents(EventListener& otherHandler);
	void Clear();

	bool IsGameOnGoing();
	bool IsGameFinished();
	bool IsGameOnPause();
	void Quit();

private:
	void LoadTextures(RendererObj* rendererObj);
	void LoadFonts();
	void RegisterEvent(SDLEventHandler& handler);

	unique_ptr<BoardHandler> boardHandler;
	shared_ptr<Text> pointsText;
	unique_ptr<FontsManager> fontsManager;
	GameState gameState;
	deque<shared_ptr<Object>> objs;
};
