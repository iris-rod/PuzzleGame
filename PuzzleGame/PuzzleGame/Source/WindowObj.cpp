#include "WindowObj.h"

WindowObj::WindowObj() {
	ptr_window = {
		SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN),
		&SDL_DestroyWindow
	};
	if (!ptr_window.get()) {
		throw "Could not create window!";
	}

	ptr_surface = { SDL_GetWindowSurface(ptr_window.get()), &SDL_FreeSurface };
	if (!ptr_surface.get()) {
		throw "Could not get window surface!";
	}
}

SDL_Surface* WindowObj::GetSurface() const {
	return ptr_surface.get();
}

SDL_Window* WindowObj::GetWindow() const {
	return ptr_window.get();
}

