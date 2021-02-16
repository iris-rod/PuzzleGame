#pragma once
#include "Object.h"
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

using namespace std;

class Text : public Object{
private:
	TTF_Font* font = nullptr;
	SDL_Color color;

public:
	
	Text(int x, int y, string text, vector<int> rgba, TTF_Font* _font, SDL_Renderer* renderer);
	void Update(string newText, SDL_Renderer* renderer);

};

