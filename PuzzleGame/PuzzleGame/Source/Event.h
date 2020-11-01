#pragma once

enum EventType {
	PIECE_REMOVED
};

class Event {
public:
	EventType type;
	Event(EventType _type);
};
