#include <SDL.h>
#include <iostream>
#include "WindowObj.h"

using namespace std;

int main(int argc, char* args[]) {
	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	WindowObj* window_obj = new WindowObj();
	SDL_Surface* surface = window_obj->GetSurface();

	// Fill the window with a white rectangle
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

	// Update the window display
	SDL_UpdateWindowSurface(window_obj->GetWindow());

	// Wait
	system("pause");

	// Destroy the window. This will also destroy the surface

}