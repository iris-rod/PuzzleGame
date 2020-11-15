#pragma once
#include <functional>
#include <map>
#include <vector>
#include <deque>
#include "Event.h"

class EventListener {
public:
	EventListener();
	~EventListener();
	using Handler = std::function<void(Event const&)>;

	void Subscribe(const int type, const Handler callback);
	void UnsubscribeEventType(const int type);
	void UnsubscribeAll();
	void NotifyEvent(const Event* e);
	void HandleEvents();

private:
	std::map<int, std::vector<Handler>> _subscribedCallbacks;
	std::deque<const Event*> triggeredEvents;
};