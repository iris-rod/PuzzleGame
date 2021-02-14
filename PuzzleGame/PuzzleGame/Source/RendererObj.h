#pragma once
#include "WindowObj.h"
#include "Object.h"
#include "TextureManager.h"
#include "Text.h"
#include <SDL.h>
#include <memory>
#include <deque>

using namespace std;

class RendererObj {
public:
	RendererObj(SDL_Window* window_obj);
	//~RendererObj();

	SDL_Renderer* GetRenderer();
	void Render(deque<shared_ptr<Object>>& objs, Text* text);

	RendererObj(const RendererObj&) = delete;
	RendererObj& operator=(const RendererObj&) = delete;

private:
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> ptr_renderer{ nullptr, &SDL_DestroyRenderer };

};
