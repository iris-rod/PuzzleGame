#include "GameManager.h"
#include <iostream>

void GameManager::Render(RendererObj* rendererObj) {
	rendererObj->Render(objs);
}

void GameManager::Init(RendererObj* rendererObj) {
	LoadTextures(rendererObj);
	boardHandler = new BoardHandler();
	boardHandler->Init();
	for (auto obj : boardHandler->GetObjs()) {
		objs.push_back(obj);
	}	
}

void GameManager::LoadTextures(RendererObj* rendererObj) {
	TextureManager::LoadTexture("red", rendererObj->GetRenderer(), "../red.png");
	TextureManager::LoadTexture("blue", rendererObj->GetRenderer(), "../blue.png");
	TextureManager::LoadTexture("yellow", rendererObj->GetRenderer(), "../yellow.png");
	TextureManager::LoadTexture("green", rendererObj->GetRenderer(), "../green.png");
	TextureManager::LoadTexture("orange", rendererObj->GetRenderer(), "../orange.png");
}