#include "GameManager.h"
#include <iostream>

void GameManager::Render(RendererObj* rendererObj) {
	rendererObj->Render(objs);
}

void GameManager::Init(RendererObj* rendererObj) {
	LoadTextures(rendererObj);
	boardHandler = new BoardHandler();
	/*SDL_Rect* src = new SDL_Rect();
	SDL_Rect* dest = new SDL_Rect();

	Ore* testOre = new Ore(1, src, dest, 10, 10, 100, 100);
	objs.push_back(testOre);*/

}

void GameManager::LoadTextures(RendererObj* rendererObj) {
	TextureManager::LoadTexture("blue", rendererObj->GetRenderer(), "../new_column.png");
}