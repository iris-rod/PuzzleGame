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
#include "Button.h"

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
	void Init(shared_ptr<RendererObj>& rendererObj, shared_ptr<SDLEventHandler>& sdlEventListener, shared_ptr<EventListener>& gameEventListener);
	void Render();
	void HandleTimeTriggeredEvents();

	bool IsGameOnGoing();
	bool IsGameFinished();
	bool IsGameOnPause();
	void Quit();

private:
	void LoadTextures();
	void LoadFonts();
	void InitInterface();
	void InitBackground();
	void ClearObjects();
	void RegisterSDLEvent();
	void RegisterGameEvent();
	bool CheckClickedOnAddColumn(const int x, const int y);

	deque<shared_ptr<Object>> objs;

	shared_ptr<Text> infoText;
	shared_ptr<Button> addColumnButton;
	shared_ptr<Object> background;

	unique_ptr<BoardHandler> boardHandler;
	unique_ptr<FontsManager> fontsManager;
	unique_ptr<PointSystem> pointSystem;
	GameState gameState;
	shared_ptr<RendererObj> rendererObj;
	shared_ptr<EventListener> gameEventListener;
	shared_ptr<SDLEventHandler> sdlEventListener;

	unique_ptr<TimeHandler> timeHandlerNewColumn;
	unique_ptr<TimeHandler> timeHandlerInfoText;

	

};
