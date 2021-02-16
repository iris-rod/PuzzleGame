#include "Piece.h"

using namespace std;
using namespace PieceStuff;

Piece::Piece(const int id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY, bool empty)
	: coordinates( new Coordinates(x, y) ), 
	boardPosition( new BoardPosition(x == 0 ? 0 : (x - START_X)/_sizeX, y == 0 ? 0 : (y - START_Y)/_sizeY) ), 
	InteractiveObject("piece" + id, _src, _dest, _sizeX, _sizeY) {
	src->x = 0;
	src->y = 0;
	dest->x = x;
	dest->y = y;
	src->w = _sizeX;
	src->h = _sizeY;
	dest->w = _sizeX;
	dest->h = _sizeY;
	neighbours = list<unique_ptr<NeighbourInfo>>();

	if (empty)	color = make_unique<Colors>(Colors::EMPTY);
	else color = make_unique<Colors>(GetRandomColor());

	textureId = ConvertColorToTextureId(*(color.get()));
}

Piece::~Piece() {
	neighbours.clear();
	neighbours.resize(0);
}

void Piece::GenerateNewColor() {
	color = make_unique<Colors>(GetRandomColor());
	textureId = ConvertColorToTextureId(*(color.get()));
}

void Piece::Swap(Piece& b) {

	auto text = b.textureId;
	b.textureId = textureId;
	textureId = text;

}

const BoardPosition& Piece::GetBoardPosition() const {
	return *boardPosition.get();
}

const Coordinates& Piece::GetCoordinates() const {
	return *coordinates.get();
}

void Piece::ClearNeighbours() {
	neighbours.clear();
	neighbours.resize(0);
}

void Piece::AddNeighbour(const bool _canRemove, const int _x, const int _y, const Direction dir) {
	neighbours.push_front(make_unique<NeighbourInfo>(_canRemove, _x, _y, dir));
}

void Piece::printNeigh() {
	for (auto i = neighbours.begin(); i != neighbours.end(); ++i) {
		cout << i->get()->canRemove << " - ";
		if(i->get()->direction == Direction::EAST)
			cout << "east" << endl;

		if (i->get()->direction == Direction::WEST)
			cout << "west" << endl;

		if (i->get()->direction == Direction::NORTH)
			cout << "north" << endl;

		if (i->get()->direction == Direction::SOUTH)
			cout << "south" << endl;

	}
}

NeighbourInfo* Piece::GetNeighbour(const Piece& piece) {
	auto position = piece.GetBoardPosition();
	auto a = find_if(neighbours.begin(), neighbours.end(), [position](unique_ptr<NeighbourInfo>& arg) {
		return *(arg.get()->position) == position;
	});
	if(a != neighbours.end())
		return (*a).get();
	return nullptr;
}

bool Piece::IsEmpty() {
	return textureId == "empty";
}

bool Piece::CanRemove() {
	auto a = find_if(neighbours.begin(), neighbours.end(), [](unique_ptr<NeighbourInfo>& arg) {
		return arg.get()->canRemove;
	});

	return a != neighbours.end();
}

void Piece::Remove(EventListener* otherHandler) {
	Remove();
	otherHandler->NotifyEvent(new EventColumnUpdate(GetBoardPosition().x));
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
		auto& piece = event_p.GetPiece();

		auto neigh = GetNeighbour(piece);
		if (neigh != nullptr && neigh->canRemove) {
			Event* event_p = new EventPieceRemoved(*this);
			handler.NotifyEvent(event_p);

			if (neigh->direction == Direction::EAST || neigh->direction == Direction::WEST) {
			}

			Remove(&handler);
			RemoveNeighbour(piece);
		}
	});
}

void Piece::RemoveNeighbour(const Piece& piece) {
	auto a = find_if(neighbours.begin(), neighbours.end(), [&piece](unique_ptr<NeighbourInfo>& arg) {
		return *(arg.get()->position) == piece.GetBoardPosition();
	});

	if (a != neighbours.end()) {
		for (auto& neigh : neighbours) {
			if (neigh.get() == (*a).get()) {
				neigh = move(make_unique<NeighbourInfo>(false, (*a)->position->x, (*a)->position->y, (*a)->direction));
				break;
			}
		}
	}
}

EventPieceRemoved::EventPieceRemoved(const Piece& _piece) : piece(&_piece), Event(PIECE_REMOVED)
{

}

const Piece& EventPieceRemoved::GetPiece() const {
	return *piece;
}
