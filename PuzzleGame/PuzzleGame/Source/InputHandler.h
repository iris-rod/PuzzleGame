#pragma once
#include <memory>
#include "EventHandler.h"

class InputHandler {
public:
	InputHandler();
	~InputHandler();
	void RegisterInput(const Uint32 type, const EventHandler::EventCallback callback);

private:
	std::unique_ptr<EventHandler> eventHandler_ptr;
};