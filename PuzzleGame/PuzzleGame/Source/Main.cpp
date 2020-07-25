#include <SDL.h>
#include <iostream>
#include "WindowObj.h"
#include "RendererObj.h"
#include "GameManager.h"

using namespace std;

int main(int argc, char* args[]) {

	GameManager gameManager = GameManager();
	bool isRunning = true;
	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}			

	WindowObj* window_obj = new WindowObj();
	RendererObj* renderer_obj = new RendererObj(window_obj->GetWindow());
	gameManager.Init(renderer_obj);

	while (isRunning) {
		try {

			gameManager.Render(renderer_obj);
			//SDL_Surface* surface = window_obj->GetSurface();
			SDL_Event _event;
			SDL_PollEvent(&_event);

			switch (_event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
			isRunning = false;
		}
	}
	
	// Fill the window with a white rectangle
	//SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

	// Update the window display
	//SDL_UpdateWindowSurface(window_obj->GetWindow());

	// Wait

	// Destroy the window. This will also destroy the surface

}