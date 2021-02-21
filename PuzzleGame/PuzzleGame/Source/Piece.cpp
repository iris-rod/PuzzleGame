#include "Piece.h"

using namespace std;
using namespace PieceStuff;

Piece::Piece(const int id, const int x, const int y, const int _sizeX, const int _sizeY, bool empty)
	: boardPosition( new BoardPosition(x == 0 ? 0 : (x - START_X)/_sizeX, y == 0 ? 0 : (y - START_Y)/_sizeY) ), 
	InteractiveObject("piece" + id, x, y, _sizeX, _sizeY) {

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

void Piece::ClearNeighbours() {
	neighbours.clear();
	neighbours.resize(0);
}

void Piece::AddNeighbour(const bool _canRemove, const int _x, const int _y, const Direction dir) {
	neighbours.push_front(make_unique<NeighbourInfo>(_canRemove, _x, _y, dir));
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

void Piece::MakeEmpty() {
	color.reset();
	color = make_unique<Colors>(Colors::EMPTY);
	textureId = ConvertColorToTextureId(*(color.get()));
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
	otherHandler->NotifyEvent(new Event(ADD_POINTS));
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
