#include <SDL.h>
#include <iostream>
#include "WindowObj.h"
#include "RendererObj.h"
#include "GameManager.h"

using namespace std;

int main(int argc, char* args[]) {

	GameManager* gameManager = new GameManager();

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}			

	if (TTF_Init() < 0) {
		cout << "Error initializing TTF: " << TTF_GetError() << endl;
		system("pause");
		return 1;
	}

	WindowObj* window_obj = new WindowObj();
	shared_ptr<RendererObj> renderer_obj = make_shared<RendererObj>(window_obj->GetWindow());
	shared_ptr<SDLEventHandler> event_handler = make_shared<SDLEventHandler>();
	shared_ptr<EventListener> other_handler = make_shared<EventListener>();
	gameManager->Init(renderer_obj, event_handler, other_handler);

	while (gameManager->IsGameOnGoing()) {
		try {
			gameManager->HandleTimeTriggeredEvents();
			other_handler->HandleEvents();
			event_handler->HandleEvents();
			gameManager->Render();
		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
			gameManager->Quit();
		}
	}

	delete window_obj;
	delete gameManager;
}