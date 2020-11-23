#include "Event.h"

Event::Event(EventType _type) : type(_type) {

}

const int EventColumnUpdate::GetColumn() const {
	return column;
}