#pragma once
#include "Object.h"
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Text : public Object{
private:
	TTF_Font* font = nullptr;
	SDL_Color color;
	unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> messageText = { nullptr, &SDL_DestroyTexture };
	bool hasText;

	void SetHasText(string text);

public:
	
	Text(int x, int y, string text, vector<int> rgba, TTF_Font* _font, SDL_Renderer* renderer);
	void Update(string newText, SDL_Renderer* renderer);
	void UpdateColor(vector<int> rgba);
	SDL_Texture* GetTexture() const;
	const bool IsDisplayed() const;
};

