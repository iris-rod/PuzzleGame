#include "Text.h"

Text::Text(int x, int y, string text, vector<int> rgba, TTF_Font* _font, SDL_Renderer* renderer) {

	font = _font;
	textureId = "text";

	SDL_Rect* _rect = new SDL_Rect();
	_rect->x = x;
	_rect->y = y;
	_rect->h = 30;

	color = SDL_Color();
	if (rgba.size() == 4) {
		color.r = 0;
		color.g = 255;
		color.b = 0;
		color.a = 255;
	}
	else {
		cout << "No proper color proveded!" << endl;
		return;
	}

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color); 
	if (surfaceMessage != nullptr) {
		_rect->w = surfaceMessage->w;
		dest = _rect;

		messageText = { SDL_CreateTextureFromSurface(renderer, surfaceMessage), &SDL_DestroyTexture }; //now you can convert it into a texture
		SDL_FreeSurface(surfaceMessage);
	}
	else {
		cout << "Couldn't create surface message!" << endl;
		return;
	}

}

void Text::Update(string newText, SDL_Renderer* renderer) {

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, newText.c_str(), color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	dest->w = surfaceMessage->w;

	messageText.reset(SDL_CreateTextureFromSurface(renderer, surfaceMessage)); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);
}

SDL_Texture* Text::GetTexture() const {
	return messageText.get();
}


