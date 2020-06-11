#include "WindowObj.h"

WindowObj::WindowObj() {

	SDL_Window* window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!window) {
		throw "Could not create window!";
	}
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	if (!surface) {
		throw "Could not get window surface!";
	}

	ptr_window = { window, &SDL_DestroyWindow };
	ptr_surface = { surface, &SDL_FreeSurface };
}

SDL_Surface* WindowObj::GetSurface() const {
	return ptr_surface.get();
}

SDL_Window* WindowObj::GetWindow() const {
	return ptr_window.get();
}
