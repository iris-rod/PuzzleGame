#pragma once
#include <memory>
#include "Text.h"
#include "FontsManager.h"
#include "RendererObj.h"
#include "EventHandler.h"
#include "Consts.h"

using namespace std;

class PointSystem {
public:
	PointSystem(shared_ptr<EventListener>& handler);
	
	void InitPointsText(FontsManager* fontsManager, RendererObj* renderer);
	void UpdatePointsText(SDL_Renderer* rendererObj);
	void Restart();
	shared_ptr<Text>& GetTextObj();

private:
	shared_ptr<Text> pointsTextObj = nullptr;
	int points = 0;
	int nextLevelPoints = STARTING_NEXT_LEVEL_POINTS;
	string title = "Points: ";
	string pointsText = "";
	bool canAddPoints = true;

	void RegisterEvents(shared_ptr<EventListener>& handler);
};

