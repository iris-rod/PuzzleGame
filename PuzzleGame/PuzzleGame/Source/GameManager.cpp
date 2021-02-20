#include "GameManager.h"
#include <iostream>
#include <time.h>

GameManager::GameManager() : boardHandler(nullptr), pointSystem(nullptr), fontsManager(nullptr) {
	timeHandlerNewColumn = make_unique<TimeHandler>();
	timeHandlerInfoText = make_unique<TimeHandler>();
}

void GameManager::Render() {
	ClearObjects();
	for (auto& obj : boardHandler->GetObjs()) {
		objs.push_back(obj);
	}
	objs.push_back(pointSystem->GetTextObj());
	objs.push_back(infoText);
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

	infoText = make_shared<Text>(200, 20, " ", vector<int>{ 0, 0, 0, 255 }, fontsManager->GetFont("../MAIAN.ttf"), rendererObj->GetRenderer());

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
		ClearObjects();
		infoText->UpdateColor(vector<int>{ 0, 200, 0, 255 });
		infoText->Update("NICE! NEXT LEVEL", rendererObj->GetRenderer());
		timeHandlerNewColumn->Reset();
		timeHandlerInfoText->Reset();
	});
	
	handler.Subscribe(END_GAME, [&](Event const& _event) {
		boardHandler->Restart();
		pointSystem->UpdatePointsText(rendererObj->GetRenderer());
		ClearObjects();
		infoText->UpdateColor(vector<int>{ 200, 0, 0, 255 });
		infoText->Update("YOU LOST", rendererObj->GetRenderer());
		timeHandlerNewColumn->Reset();
		timeHandlerInfoText->Reset();
	});
}

void GameManager::HandleTimeTriggeredEvents(EventListener& otherHandler) {
	if (timeHandlerNewColumn->GetElapsedTime() >= NEW_COLUMN_TIME) {
		boardHandler->AddColumn();
		boardHandler->HandleAddedNewColumn(otherHandler);
		timeHandlerNewColumn->Reset();
	}	

	if (timeHandlerInfoText->GetElapsedTime() >= SHOW_INFO_TEXT_TIME && infoText->IsDisplayed() ) {
		infoText->Update(" ", rendererObj->GetRenderer());
		timeHandlerInfoText->Reset();
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

void GameManager::ClearObjects() {
	objs.clear();
	objs.resize(0);
}