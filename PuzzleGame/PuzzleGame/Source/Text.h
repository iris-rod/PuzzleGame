#pragma once
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

using namespace std;

class Text {
private:
	TTF_Font* font;
	SDL_Rect rect;
	SDL_Texture* message;
	SDL_Color color;

public:
	
	Text(int x, int y, string text, vector<int> rgba, TTF_Font* _font, SDL_Renderer* renderer);
	void Update(string newText, SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
	SDL_Texture* GetMessage();
	SDL_Rect GetRect();

};

