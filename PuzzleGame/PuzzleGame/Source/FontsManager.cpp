#include "FontsManager.h"

FontsManager::FontsManager() {
	fonts = map<string, unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>>();
}

void FontsManager::AddFont(const char* fontName) {
	auto newFont = TTF_OpenFont(fontName, 20);
	std::cout << TTF_GetError() << std::endl;
	unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> f = { newFont, &TTF_CloseFont };

	fonts.insert(pair<string, unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>>(fontName, move(f)));
}

TTF_Font* FontsManager::GetFont(string name) {
	auto a = fonts.at(name).get();
	return a;
}

