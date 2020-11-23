#include "EventHandler.h"
#include <iostream>

using namespace std;

EventListener::EventListener() {

}

EventListener::~EventListener() {
	UnsubscribeAll();
	triggeredEvents = std::priority_queue<const Event*, std::vector<const Event*>, comparator>();
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

void EventListener::NotifyEvent(const Event* e) {
	triggeredEvents.push(e);
}

void EventListener::HandleEvents() {
	while (!triggeredEvents.empty()) {
		auto current_event = triggeredEvents.top();
		cout << current_event->type << endl;
		for (auto& cb : _subscribedCallbacks[current_event->type]) {
			cb(*current_event);
		}
		triggeredEvents.pop();		
	}
}
