#include "Piece.h"

using namespace std;

Piece::Piece(const int id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY) 
	: coordinates( new Coordinates(x, y) ), 
	boardPosition( new BoardPosition(x == 0 ? 0 : x/_sizeX, y == 0 ? 0 : y/_sizeY) ), 
	InteractiveObject("piece" + id, _src, _dest, _sizeX, _sizeY) {
	//std::cout << (x == 0 ? 0 : x / _sizeX) << ", " << (y == 0 ? 0 : y / _sizeY) << std::endl;
	src->x = 0;
	src->y = 0;
	dest->x = x;
	dest->y = y;
	src->w = _sizeX;
	src->h = _sizeY;
	dest->w = _sizeX;
	dest->h = _sizeY;
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
	std::cout << "has neighbout" << std::endl;
	auto a =  find_if(neighbours.begin(), neighbours.end(), [piece](NeighbourInfo* arg) {
		return arg->position == piece->GetBoardPosition();
	});

	cout << *a << endl;

	return a != neighbours.end();
}

bool Piece::CanRemove() {
	std::cout << "can remove" << std::endl;
	auto a = find_if(neighbours.begin(), neighbours.end(), [](NeighbourInfo* arg) {
		return arg->canRemove;
	});

	return a != neighbours.end();
}

void Piece::Remove() {
	//clean neighbours
}


/*
 bool CanRemove(EventHandler otherHandler) {
	
	otherHandler.notifyEvent();
 }
*/

void Piece::RegisterEvents(EventListener& handler) {
	handler.Subscribe(PIECE_REMOVED, [this](Event const& _event) {
		Event& nonConstEvent = const_cast<Event&>(_event);
		EventPieceRemoved& p = dynamic_cast<EventPieceRemoved&>(nonConstEvent);
		if (HasNeighbour(&(p.GetPiece()))) {
			std::cout << "trigger removed" << std::endl;
			//remove from neighbours
		}
	});
}




EventPieceRemoved::EventPieceRemoved(Piece& _piece) : piece(_piece), Event(PIECE_REMOVED)
{

}

const Piece& EventPieceRemoved::GetPiece() const {
	return piece;
}
