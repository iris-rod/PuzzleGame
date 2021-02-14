#pragma once

#include <SDL_ttf.h>
#include <map>
#include <memory>
#include <iostream>

using namespace std;

class FontsManager {
private:
	map<string, unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>> fonts = map<string, unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>>();

public:
	FontsManager();
	void AddFont(const char* fontName);
	TTF_Font* GetFont(string name);

	FontsManager(const FontsManager&) = delete;
	FontsManager& operator=(const FontsManager&) = delete;
};
