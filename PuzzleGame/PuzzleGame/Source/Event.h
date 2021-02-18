#pragma once

enum EventType {
	ADD_POINTS = 1,
	NEXT_LEVEL = 2,
	PIECE_REMOVED = 3,
	COLUMN_UPDATE = 4,
	EMPTY_COLUMN = 5
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
	int GetColumn() const;
};

class EventEmptyColumn : public Event {
private:
	int column;

public:
	EventEmptyColumn(const int _column) : column(_column), Event(EMPTY_COLUMN) {};
	int GetColumn() const;
};