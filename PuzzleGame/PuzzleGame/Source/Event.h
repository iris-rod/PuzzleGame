#pragma once
#include "Piece.h"

enum EventType {
	PIECE_REMOVED
};


class Event {
public:
	const EventType type;
	Event(EventType _type) : type(_type) {}
};

class EventPieceRemoved : public Event {
private:
	const Piece& piece;

public:
	EventPieceRemoved(Piece& _piece) : piece(_piece), Event(PIECE_REMOVED) {}
	const Piece& GetPiece() const { return piece; };
};
