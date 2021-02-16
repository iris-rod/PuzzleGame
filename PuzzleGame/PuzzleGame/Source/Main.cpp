#include <SDL.h>
#include <iostream>
#include "WindowObj.h"
#include "RendererObj.h"
#include "GameManager.h"

using namespace std;

int main(int argc, char* args[]) {

	GameManager* gameManager = new GameManager();
	bool isRunning = true;
	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}			

	if (TTF_Init() < 0) {
		cout << "Error initializing TTF: " << TTF_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	WindowObj* window_obj = new WindowObj();
	shared_ptr<RendererObj> renderer_obj = make_shared<RendererObj>(window_obj->GetWindow());
	SDLEventHandler event_handler = SDLEventHandler();
	EventListener other_handler = EventListener();
	gameManager->Init(renderer_obj, event_handler, other_handler);

	while (gameManager->IsGameOnGoing()) {
		try {
			gameManager->HandleTimeTriggeredEvents(other_handler);
			other_handler.HandleEvents();
			event_handler.HandleEvents();
			gameManager->Render();
		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
			gameManager->Quit();
		}
	}

	delete window_obj;
	delete gameManager;
	
	// Fill the window with a white rectangle
	//SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

	// Update the window display
	//SDL_UpdateWindowSurface(window_obj->GetWindow());

	// Wait

	// Destroy the window. This will also destroy the surface

}