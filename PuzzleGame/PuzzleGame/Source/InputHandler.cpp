#include "InputHandler.h"

InputHandler::InputHandler() : eventHandler_ptr(std::make_unique<EventHandler>(new EventHandler())) {

}

void InputHandler::RegisterInput(const Uint32 type, const EventHandler::EventCallback callback) {
	eventHandler_ptr->Subscribe(type, callback);
}