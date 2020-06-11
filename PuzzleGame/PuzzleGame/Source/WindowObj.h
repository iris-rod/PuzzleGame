#pragma once
#include <SDL.h>
#include <memory>

class WindowObj {
public:
	WindowObj();
	~WindowObj();
	SDL_Window* GetWindow() const;
	SDL_Surface* GetSurface() const;

private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> ptr_window{ nullptr, &SDL_DestroyWindow };
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> ptr_surface{ nullptr, &SDL_FreeSurface};
	WindowObj(const WindowObj&);
	WindowObj& operator=(const WindowObj&);
};