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

void EventListener::NotifyEvent(Event e) {
	triggeredEvents.push_back(e);
}

void EventListener::HandleEvents() {
	while (!triggeredEvents.empty()) {
		auto current_event = triggeredEvents.front();
		for (auto& cb : _subscribedCallbacks[current_event]) {
			cb(current_event);
		}
		triggeredEvents.pop_front();		
	}
}
