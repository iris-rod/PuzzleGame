#include "EventHandler.h"

void EventHandler::Subscribe(const Uint32 type, const EventCallback callback) {
	_subscribedCallbacks[type].push_back(callback);
}

void EventHandler::UnsubscribeEventType(const Uint32 type) {
	_subscribedCallbacks.erase(type);
}

void EventHandler::UnsubscribeAll() {
	_subscribedCallbacks.clear();
}

void EventHandler::HandleEvents() {
	SDL_Event current_event;
	while (SDL_PollEvent(&current_event) != 0) {
		for (auto& cb : _subscribedCallbacks[current_event.type]) {
			cb(current_event);
		}
	}
}
