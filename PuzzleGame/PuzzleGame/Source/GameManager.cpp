#include "GameManager.h"
#include <iostream>
#include <time.h>

GameManager::GameManager() : boardHandler(nullptr), pointSystem(nullptr), fontsManager(nullptr) {
	timeHandlerNewColumn = make_unique<TimeHandler>();
	timeHandlerInfoText = make_unique<TimeHandler>();
}

void GameManager::Render() {
	ClearObjects();
	objs.push_back(background);
	for (auto& obj : boardHandler->GetObjs()) {
		objs.push_back(obj);
	}
	objs.push_back(pointSystem->GetTextObj());
	objs.push_back(infoText);
	objs.push_back(addColumnButton);
	rendererObj->Render(objs);
}

void GameManager::Init(shared_ptr<RendererObj>& _rendererObj, shared_ptr<SDLEventHandler>& _sdlEventListener, shared_ptr<EventListener>& _gameEventListener) {
	srand(time(NULL));
	rendererObj = _rendererObj;
	gameEventListener = _gameEventListener;
	sdlEventListener = _sdlEventListener;
	LoadTextures();

	background = make_shared<Object>("background", 0, 0, 1200, 600);
	background->SetTexture("background");
	boardHandler = make_unique<BoardHandler>();
	boardHandler->Init(_sdlEventListener, _gameEventListener);

	InitInterface();

	RegisterSDLEvent();
	RegisterGameEvent();

	gameState = GameState::ON_GOING;
}

void GameManager::InitInterface() {
	fontsManager = make_unique<FontsManager>();
	LoadFonts();
	pointSystem = make_unique<PointSystem>(gameEventListener);
	pointSystem->InitPointsText(fontsManager.get(), rendererObj.get());

	infoText = make_shared<Text>(200, 20, " ", vector<int>{ 0, 0, 0, 255 }, fontsManager->GetFont("../assets/MAIAN.ttf"), rendererObj->GetRenderer());

	addColumnButton = make_shared<Button>(0, 960, 20, 30, 30);
	addColumnButton->SetImage("new_column");
}

void GameManager::LoadFonts() {
	fontsManager->AddFont("../assets/MAIAN.ttf");
}

void GameManager::LoadTextures() {
	TextureManager::LoadTexture("red", rendererObj->GetRenderer(), "../assets/red.png");
	TextureManager::LoadTexture("blue", rendererObj->GetRenderer(), "../assets/blue.png");
	TextureManager::LoadTexture("yellow", rendererObj->GetRenderer(), "../assets/yellow.png");
	TextureManager::LoadTexture("green", rendererObj->GetRenderer(), "../assets/green.png");
	TextureManager::LoadTexture("orange", rendererObj->GetRenderer(), "../assets/orange.png");
	TextureManager::LoadTexture("empty", rendererObj->GetRenderer(), "../assets/empty.png");
	TextureManager::LoadTexture("new_column", rendererObj->GetRenderer(), "../assets/new_column.png");
	TextureManager::LoadTexture("background", rendererObj->GetRenderer(), "../assets/background.png");
}

void GameManager::RegisterSDLEvent() {
	sdlEventListener->Subscribe(SDL_QUIT, [this](SDL_Event const& event) {
		if (event.type == SDL_QUIT) {
			Quit();
		}
	});

	sdlEventListener->Subscribe(SDL_KEYDOWN, [this](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			Quit();
		}
	});	

	sdlEventListener->Subscribe(SDL_MOUSEBUTTONDOWN, [&](SDL_Event const& event) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (CheckClickedOnAddColumn(x, y)) {
			boardHandler->AddColumn();
			boardHandler->HandleAddedNewColumn(gameEventListener);
			timeHandlerNewColumn->Reset();
		}
	});
}

bool GameManager::CheckClickedOnAddColumn(const int x, const int y) {
	auto addColumnCoordinates = addColumnButton->GetCoordinates();
	if (x >= addColumnCoordinates.x && x < addColumnCoordinates.x + PIECE_SIZE_X
		&& y >= addColumnCoordinates.y && y < addColumnCoordinates.y + PIECE_SIZE_Y) {
		return true;
	}
	return false;
}

void GameManager::RegisterGameEvent() {
	gameEventListener->Subscribe(ADD_POINTS, [&](Event const& _event) {
		pointSystem->UpdatePointsText(rendererObj->GetRenderer());
	});

	gameEventListener->Subscribe(NEXT_LEVEL, [&](Event const& _event) {
		boardHandler->Restart();
		pointSystem->UpdatePointsText(rendererObj->GetRenderer()); 
		ClearObjects();
		infoText->UpdateColor(vector<int>{ 0, 200, 0, 255 });
		infoText->Update("NICE! NEXT LEVEL", rendererObj->GetRenderer());
		timeHandlerNewColumn->Reset();
		timeHandlerInfoText->Reset();
	});
	
	gameEventListener->Subscribe(END_GAME, [&](Event const& _event) {
		boardHandler->Restart();
		pointSystem->UpdatePointsText(rendererObj->GetRenderer());
		ClearObjects();
		infoText->UpdateColor(vector<int>{ 200, 0, 0, 255 });
		infoText->Update("YOU LOST", rendererObj->GetRenderer());
		timeHandlerNewColumn->Reset();
		timeHandlerInfoText->Reset();
	});
}

void GameManager::HandleTimeTriggeredEvents() {
	if (timeHandlerNewColumn->GetElapsedTime() >= NEW_COLUMN_TIME) {
		boardHandler->AddColumn();
		boardHandler->HandleAddedNewColumn(gameEventListener);
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