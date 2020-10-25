#pragma once
#include <functional>
#include <map>
#include <vector>
#include <deque>

enum Event {
	PIECE_REMOVED
};

class EventListener {
public:
	EventListener();
	//~EventHandler();
	using Handler = std::function<void(Event const&)>;

	void Subscribe(const int type, const Handler callback);
	void UnsubscribeEventType(const int type);
	void UnsubscribeAll();
	void NotifyEvent(Event e);
	void HandleEvents();

private:
	std::map<int, std::vector<Handler>> _subscribedCallbacks;
	std::deque<Event> triggeredEvents;
};