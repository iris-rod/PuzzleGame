#include "SDLEventHandler.h"
#include <iostream>

SDLEventHandler::SDLEventHandler() {

}

SDLEventHandler::~SDLEventHandler() {
	UnsubscribeAll();
}

void SDLEventHandler::Subscribe(const Uint32 type, const EventCallback callback) {
	_subscribedCallbacks[type].push_back(callback);
}

void SDLEventHandler::UnsubscribeEventType(const Uint32 type) {
	_subscribedCallbacks.erase(type);
}

void SDLEventHandler::UnsubscribeAll() {
	_subscribedCallbacks.clear();
}

void SDLEventHandler::HandleEvents() {
	SDL_Event current_event;
	if (SDL_PollEvent(&current_event) != 0) {
		for (auto& cb : _subscribedCallbacks[current_event.type]) {
			cb(current_event);
		}
	}
}
