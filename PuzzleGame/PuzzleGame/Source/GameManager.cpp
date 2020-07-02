#include "GameManager.h"
#include <iostream>

void GameManager::Render(RendererObj* rendererObj) {
	rendererObj->Render(objs);
}

void GameManager::Init(RendererObj* rendererObj) {
	std::cout << rendererObj->GetRenderer() << std::endl;
	TextureManager::LoadTexture("blue", rendererObj->GetRenderer(), "C://Users//IrisRodrigues//Documents//personal//C++//PuzzleGame//PuzzleGame//new_column.png");

	SDL_Rect src = SDL_Rect();
	SDL_Rect dest = SDL_Rect();

	Ore* testOre = new Ore(1, &src, &dest, 10, 10);
	std::cout << "add ore to objs list on game manager" << std::endl;
	objs.push_back(testOre);
}