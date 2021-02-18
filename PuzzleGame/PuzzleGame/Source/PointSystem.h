#pragma once
#include <memory>
#include "Text.h"
#include "FontsManager.h"
#include "RendererObj.h"
#include "EventHandler.h"

using namespace std;

class PointSystem {
public:
	PointSystem(EventListener& handler);
	
	void InitPointsText(FontsManager* fontsManager, RendererObj* renderer);
	void UpdatePointsText(SDL_Renderer* rendererObj);
	void Restart();
	shared_ptr<Text>& GetTextObj();

private:
	shared_ptr<Text> pointsTextObj = nullptr;
	int points = 0;
	int nextLevelPoints = 5;
	string title = "Points: ";
	string pointsText = "";
	bool canAddPoints = true;

	void RegisterEvents(EventListener& handler);
};

