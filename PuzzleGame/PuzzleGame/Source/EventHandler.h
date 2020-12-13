#pragma once
#include <functional>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include "Event.h"

struct comparator {
	bool operator()(const Event* i, const Event* j) {
		return i->type > j->type;
	}
};

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
	std::priority_queue<const Event*, std::vector<const Event*>, comparator> triggeredEvents;
};