#pragma once
#include "SDL.h"
#include <functional>
#include <map>
#include <vector>

class SDLEventHandler {
public:
	SDLEventHandler();
	~SDLEventHandler();
	using EventCallback = std::function<void(SDL_Event const&)>;

	void Subscribe(const Uint32 type, const EventCallback callback);
	void UnsubscribeEventType(const Uint32 type);
	void UnsubscribeAll();

	void HandleEvents();

private:
	std::map<Uint32, std::vector<EventCallback>> _subscribedCallbacks;	
};