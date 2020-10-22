#pragma once
#include <functional>
#include <map>
#include <vector>

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

	void HandleEvents(Event current_event);

private:
	std::map<int, std::vector<Handler>> _subscribedCallbacks;
};