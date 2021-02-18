#include "GameManager.h"
#include "TimeHandler.h"
#include <iostream>
#include <time.h>

GameManager::GameManager() : boardHandler(nullptr), pointSystem(nullptr), fontsManager(nullptr) {
	TimeHandler::Start();
}

void GameManager::Render() {
	objs.clear();
	objs.resize(0);
	for (auto& obj : boardHandler->GetObjs()) {
		objs.push_back(obj);
	}
	objs.push_back(pointSystem->GetTextObj());
	rendererObj->Render(objs);
}

void GameManager::Init(shared_ptr<RendererObj>& _rendererObj, SDLEventHandler& handler, EventListener& otherHandler) {
	srand(time(NULL));

	rendererObj = _rendererObj;
	LoadTextures();

	boardHandler = make_unique<BoardHandler>();
	fontsManager = make_unique<FontsManager>();
	LoadFonts();
	pointSystem = make_unique<PointSystem>(otherHandler);
	pointSystem->InitPointsText(fontsManager.get(), rendererObj.get());
	
	boardHandler->Init(handler, otherHandler);
	for (auto& obj : boardHandler->GetObjs()) {
		objs.push_back(obj);
	}	

	RegisterSDLEvent(handler);
	RegisterGameEvent(otherHandler);

	gameState = GameState::ON_GOING;
}

void GameManager::LoadFonts() {
	fontsManager->AddFont("../MAIAN.ttf");
}

void GameManager::LoadTextures() {
	TextureManager::LoadTexture("red", rendererObj->GetRenderer(), "../red.png");
	TextureManager::LoadTexture("blue", rendererObj->GetRenderer(), "../blue.png");
	TextureManager::LoadTexture("yellow", rendererObj->GetRenderer(), "../yellow.png");
	TextureManager::LoadTexture("green", rendererObj->GetRenderer(), "../green.png");
	TextureManager::LoadTexture("orange", rendererObj->GetRenderer(), "../orange.png");
	TextureManager::LoadTexture("empty", rendererObj->GetRenderer(), "../empty.png");
}

void GameManager::RegisterSDLEvent(SDLEventHandler& handler) {
	handler.Subscribe(SDL_QUIT, [this](SDL_Event const& event) {
		if (event.type == SDL_QUIT) {
			Quit();
		}
	});

	handler.Subscribe(SDL_KEYDOWN, [this](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			Quit();
		}
	});	
}

void GameManager::RegisterGameEvent(EventListener& handler) {
	handler.Subscribe(ADD_POINTS, [&](Event const& _event) {
		pointSystem->UpdatePointsText(rendererObj->GetRenderer());
	});

	handler.Subscribe(NEXT_LEVEL, [&](Event const& _event) {
		boardHandler->Restart();
		pointSystem->UpdatePointsText(rendererObj->GetRenderer());
		objs.clear();
		objs.resize(0);
		TimeHandler::Reset();
	});
}

void GameManager::HandleTimeTriggeredEvents(EventListener& otherHandler) {
	if (TimeHandler::GetElapsedTime() >= NEW_COLUMN_TIME) {
		boardHandler->AddColumn(otherHandler);
		TimeHandler::Reset();
	}
}

bool GameManager::IsGameFinished() {
	return gameState == GameState::FINISHED;
}

bool GameManager::IsGameOnGoing() {
	return gameState == GameState::ON_GOING;
}

bool GameManager::IsGameOnPause() {
	return gameState == GameState::ON_PAUSE;
}
void GameManager::Quit() {
	TTF_Quit();
	gameState = GameState::QUIT;
}