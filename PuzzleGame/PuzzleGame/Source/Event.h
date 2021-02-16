#pragma once

enum EventType {
	PIECE_REMOVED = 1,
	COLUMN_UPDATE = 2,
	EMPTY_COLUMN = 3,
	ADD_POINTS = 4
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