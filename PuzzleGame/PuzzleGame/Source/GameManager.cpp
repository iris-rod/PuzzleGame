#include "GameManager.h"
#include "TimeHandler.h"
#include <iostream>
#include <time.h>

GameManager::GameManager() : boardHandler(nullptr) {
	TimeHandler::Start();
}

void GameManager::Render(RendererObj* rendererObj) {
	rendererObj->Render(objs);
}

void GameManager::Init(RendererObj* rendererObj, SDLEventHandler& handler, EventListener& otherHandler) {
	srand(time(NULL));
	LoadTextures(rendererObj);
	boardHandler = make_unique<BoardHandler>();
	boardHandler->Init(handler, otherHandler);
	for (auto& obj : boardHandler->GetObjs()) {
		objs.push_back(obj);
	}	

	RegisterEvent(handler);

	gameState = GameState::ON_GOING;
}

void GameManager::LoadTextures(RendererObj* rendererObj) {
	TextureManager::LoadTexture("red", rendererObj->GetRenderer(), "../red.png");
	TextureManager::LoadTexture("blue", rendererObj->GetRenderer(), "../blue.png");
	TextureManager::LoadTexture("yellow", rendererObj->GetRenderer(), "../yellow.png");
	TextureManager::LoadTexture("green", rendererObj->GetRenderer(), "../green.png");
	TextureManager::LoadTexture("orange", rendererObj->GetRenderer(), "../orange.png");
	TextureManager::LoadTexture("empty", rendererObj->GetRenderer(), "../empty.png");
}

void GameManager::RegisterEvent(SDLEventHandler& handler) {
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

void GameManager::HandleTimeTriggeredEvents() {
	if (TimeHandler::GetElapsedTime() >= NEW_COLUMN_TIME) {
		boardHandler->AddColumn();
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
	gameState = GameState::QUIT;
}