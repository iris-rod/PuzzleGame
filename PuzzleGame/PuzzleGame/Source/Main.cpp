#include <SDL.h>
#include <iostream>
#include "WindowObj.h"

using namespace std;

int main(int argc, char* args[]) {

	WindowObj* window_obj = new WindowObj();

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	// Make sure creating the window succeeded
	if (!window_obj->GetWindow()) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	// Make sure getting the surface succeeded
	if (!window_obj->GetSurface()) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	// Fill the window with a white rectangle
	SDL_FillRect(window_obj->GetSurface(), NULL, SDL_MapRGB(window_obj->GetSurface()->format, 255, 255, 255));

	// Update the window display
	SDL_UpdateWindowSurface(window_obj->GetWindow());

	// Wait
	system("pause");

	// Destroy the window. This will also destroy the surface

}