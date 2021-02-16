#include "PointSystem.h"

PointSystem::PointSystem(EventListener& handler) {
	RegisterEvents(handler);
}


void PointSystem::InitPointsText(FontsManager* fontsManager, RendererObj* rendererObj) {
	pointsText = to_string(points);
	pointsTextObj = make_shared<Text>(20, 20, title + pointsText, vector<int>{ 0, 0, 0, 255 }, fontsManager->GetFont("../MAIAN.ttf"), rendererObj->GetRenderer());
}

void PointSystem::UpdatePointsText(SDL_Renderer* rendererObj) {
	pointsText = to_string(points);
	pointsTextObj->Update(title + pointsText, rendererObj);
}

void PointSystem::RegisterEvents(EventListener& handler) {
	handler.Subscribe(ADD_POINTS, [&](Event const& _event) {
		points++;
	});
}

shared_ptr<Text>& PointSystem::GetTextObj() {
	return pointsTextObj;
}
