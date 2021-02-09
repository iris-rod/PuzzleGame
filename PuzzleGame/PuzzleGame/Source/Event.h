#pragma once

enum EventType {
	PIECE_REMOVED = 1,
	COLUMN_UPDATE = 2,
	EMPTY_COLUMN = 3
};

class Event {
public:
	EventType type;
	Event(EventType _type);
	virtual ~Event() = default;
};

class EventColumnUpdate : public Event {
private:
	int column;

public:
	EventColumnUpdate(const int _column) : column(_column), Event(COLUMN_UPDATE) {};
	const int GetColumn() const;
};