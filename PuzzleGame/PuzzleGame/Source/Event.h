#pragma once

enum EventType {
	END_GAME = 1,
	ADD_POINTS = 5,
	NEXT_LEVEL = 6,
	PIECE_REMOVED = 4,
	COLUMN_UPDATE = 7,
	EMPTY_COLUMN = 8
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