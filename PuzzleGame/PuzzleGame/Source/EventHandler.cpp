#include "EventHandler.h"
#include <iostream>

EventListener::EventListener() {

}

void EventListener::Subscribe(const int type, const Handler callback) {
	_subscribedCallbacks[type].push_back(callback);
}

void EventListener::UnsubscribeEventType(const int type) {
	_subscribedCallbacks.erase(type);
}

void EventListener::UnsubscribeAll() {
	_subscribedCallbacks.clear();
}

void EventListener::HandleEvents(Event current_event) {
	for (auto& cb : _subscribedCallbacks[current_event]) {
		cb(current_event);
	}
}
