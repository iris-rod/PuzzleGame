#include "Piece.h"

using namespace std;
using namespace PieceStuff;

Piece::Piece(const int id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY) 
	: coordinates( new Coordinates(x, y) ), 
	boardPosition( new BoardPosition(x == 0 ? 0 : x/_sizeX, y == 0 ? 0 : y/_sizeY) ), 
	InteractiveObject("piece" + id, _src, _dest, _sizeX, _sizeY) {
	src->x = 0;
	src->y = 0;
	dest->x = x;
	dest->y = y;
	src->w = _sizeX;
	src->h = _sizeY;
	dest->w = _sizeX;
	dest->h = _sizeY;
}

Piece::~Piece() {
	neighbours.clear();
	neighbours.resize(0);
}

void Piece::operator=(const Piece& rhs) {
	this->textureId = rhs.textureId;
	RedefineNeighbours();
}

void Piece::RedefineNeighbours() {
	for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
		std::cout << (*it)->canRemove;
		//update can remove neighbour after assingning a new color
	}
}

const BoardPosition* Piece::GetBoardPosition() const {
	return boardPosition.get();
}

const Coordinates* Piece::GetCoordinates() const {
	return coordinates.get();
}

const void Piece::AddNeighbour(NeighbourInfo* neighbour) {
	neighbours.push_front(neighbour);
}

const bool Piece::HasNeighbour(const Piece* piece) {
	return GetNeighbour(piece) != nullptr;
}

NeighbourInfo* Piece::GetNeighbour(const Piece* piece) {
	auto position = piece->GetBoardPosition();
	auto a = find_if(neighbours.begin(), neighbours.end(), [position](NeighbourInfo* arg) {
		return *(arg->position) == *position;
	});
	if(a != neighbours.end())
		return *a;
	return nullptr;
}

bool Piece::IsEmpty() {
	return textureId == "empty";
}

bool Piece::CanRemove() {
	auto a = find_if(neighbours.begin(), neighbours.end(), [](NeighbourInfo* arg) {
		return arg->canRemove;
	});

	return a != neighbours.end();
}

void Piece::Remove(EventListener* otherHandler) {
	Remove();
	otherHandler->NotifyEvent(new EventColumnUpdate(GetBoardPosition()->x));
}

void Piece::Remove() {
	textureId = "empty";
	neighbours.clear();
}

void Piece::RegisterEvents(EventListener& handler) {
	handler.Subscribe(PIECE_REMOVED, [this, &handler](Event const& _event) {
		auto pos = this->GetBoardPosition();
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventPieceRemoved& event_p = dynamic_cast<EventPieceRemoved&>(nonConstEvent);
		auto piece = &(event_p.GetPiece());
		if (HasNeighbour(piece)) {
			auto neigh = GetNeighbour(piece);
			if (neigh != nullptr && neigh->canRemove) {
				Event* event_p = new EventPieceRemoved(this);
				handler.NotifyEvent(event_p);
				Remove(&handler);
			}
			RemoveNeighbour(piece);
			cout << "piece removed" << endl;
		}
	});
}

void Piece::RemoveNeighbour(const Piece* piece) {
	auto a = find_if(neighbours.begin(), neighbours.end(), [&piece](NeighbourInfo* arg) {
		return *(arg->position) == *(piece->GetBoardPosition());
	});
	
	if(a != neighbours.end())
		replace(neighbours.begin(), neighbours.end(), *a, new NeighbourInfo(false, (*a)->position->x, (*a)->position->y, (*a)->direction));
}


EventPieceRemoved::EventPieceRemoved(const Piece* _piece) : piece(_piece), Event(PIECE_REMOVED)
{

}

const Piece& EventPieceRemoved::GetPiece() const {
	return *piece;
}
