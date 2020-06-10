#include "WindowObj.h"

WindowObj::WindowObj() {
	ptr_window.reset(SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN));
	ptr_surface.reset(SDL_GetWindowSurface(ptr_window.get()));
}

WindowObj::~WindowObj() {
	
}

SDL_Surface* WindowObj::GetSurface() const {
	return ptr_surface.get();
}

SDL_Window* WindowObj::GetWindow() const {
	return ptr_window.get();
}