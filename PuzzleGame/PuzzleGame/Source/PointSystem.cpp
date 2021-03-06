#include "PointSystem.h"

PointSystem::PointSystem(shared_ptr<EventListener>& handler) {
	RegisterEvents(handler);
}


void PointSystem::InitPointsText(FontsManager* fontsManager, RendererObj* rendererObj) {
	pointsText = to_string(points);
	pointsTextObj = make_shared<Text>(20, 20, title + pointsText + "/" + to_string(nextLevelPoints), vector<int>{ 0, 0, 0, 255 }, fontsManager->GetFont("../assets/MAIAN.ttf"), rendererObj->GetRenderer());
}

void PointSystem::UpdatePointsText(SDL_Renderer* rendererObj) {
	pointsText = to_string(points);
	pointsTextObj->Update(title + pointsText + "/" + to_string(nextLevelPoints), rendererObj);
}

void PointSystem::Restart() {
	canAddPoints = true;
}

void PointSystem::RegisterEvents(shared_ptr<EventListener>& handler) {
	handler->Subscribe(ADD_POINTS, [&](Event const& _event) {
		if(canAddPoints)
			points++;

		if (points >= nextLevelPoints) {
			handler->NotifyEvent(new Event(NEXT_LEVEL));
			canAddPoints = false;
		}
	});

	handler->Subscribe(NEXT_LEVEL, [&](Event const& _event) {
		nextLevelPoints += NEW_LEVEL_POINTS_INC;
		points = 0;
		canAddPoints = true;
	});

	handler->Subscribe(END_GAME, [&](Event const& _event) {
		nextLevelPoints = STARTING_NEXT_LEVEL_POINTS;
		points = 0;
		canAddPoints = true;
	});
}

shared_ptr<Text>& PointSystem::GetTextObj() {
	return pointsTextObj;
}
