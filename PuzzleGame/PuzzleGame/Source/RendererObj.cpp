#include "RendererObj.h"
#include "SDL_image.h"
#include <iostream>

RendererObj::RendererObj(SDL_Window* window_obj) {

	SDL_Renderer* _renderer = SDL_CreateRenderer(window_obj, -1, 0);

	if (!_renderer) {
		throw "Could not create renderer!";
	}
	
	ptr_renderer = { _renderer, &SDL_DestroyRenderer };
	SDL_SetRenderDrawColor(ptr_renderer.get(), 255, 255, 255, 255);
	SDL_SetRenderDrawBlendMode(ptr_renderer.get(), SDL_BLENDMODE_BLEND);
}

SDL_Renderer* RendererObj::GetRenderer() {
	return ptr_renderer.get();
}

void RendererObj::Render(deque<shared_ptr<Object>>& objs) {
	SDL_RenderClear(ptr_renderer.get());
	for (std::deque<shared_ptr<Object>>::iterator it = objs.begin(); it != objs.end(); it++) {
		auto& currentObj = *it;

		if (currentObj->GetTextureId() != "text") 
			RenderPiece(currentObj);
		else 
			RenderText(currentObj);
	}

	SDL_RenderPresent(ptr_renderer.get());	
}

void RendererObj::RenderPiece(shared_ptr<Object> obj) {
	SDL_RenderCopy(ptr_renderer.get(), obj->GetTexture(), obj->GetSrcRect(), obj->GetDestRect());
}

void RendererObj::RenderText(shared_ptr<Object> obj) {
	SDL_RenderCopy(ptr_renderer.get(), obj->GetTexture(), NULL, obj->GetDestRect());
}