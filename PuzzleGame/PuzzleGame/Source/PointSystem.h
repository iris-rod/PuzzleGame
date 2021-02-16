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
	shared_ptr<Text>& GetTextObj();

private:
	shared_ptr<Text> pointsTextObj = nullptr;
	int points = 0;
	string title = "Points: ";
	string pointsText = "";

	void RegisterEvents(EventListener& handler);
};

