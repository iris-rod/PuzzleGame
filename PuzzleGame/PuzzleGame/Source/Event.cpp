#include "Event.h"

Event::Event(EventType _type) : type(_type) {

}

int EventColumnUpdate::GetColumn() const {
	return column;
}


int EventEmptyColumn::GetColumn() const {
	return column;
}