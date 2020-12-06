#pragma once
#include "InteractiveObject.h"
#include "EventHandler.h"
#include "Utils.h"
#include <vector>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

namespace PieceStuff {

	struct BoardPosition {
		int x;
		int y;

		BoardPosition(const int _x, const int _y) {
			x = _x;
			y = _y;
		}

		bool operator==(const BoardPosition& a) {
			return this->x == a.x && this->y == a.y;
		}

		bool operator==(const BoardPosition& a) const {
			return this->x == a.x && this->y == a.y;
		}
	};

	struct Coordinates {
		int x;
		int y;

		Coordinates(const int _x, const int _y) {
			x = _x;
			y = _y;
		}
	};

	struct NeighbourInfo {
		bool canRemove;
		const BoardPosition* position;
		Direction direction;

		NeighbourInfo(const bool _canRemove, const int _x, const int _y, const Direction dir) {
			position = new BoardPosition(_x, _y);
			canRemove = _canRemove;
			direction = dir;
		}

		bool operator==(const NeighbourInfo& a) {
			return this->position == a.position && this->canRemove == a.canRemove;
		}

		bool operator==(const NeighbourInfo& a) const {
			return this->position == a.position && this->canRemove == a.canRemove;
		}
	};

	class Piece : public InteractiveObject {
	public:
		Piece() = default;
		Piece(const int Id, SDL_Rect* _src, SDL_Rect* _dest, const int x, const int y, const int _sizeX, const int _sizeY);
		virtual ~Piece();
		const BoardPosition& GetBoardPosition() const;
		const Coordinates& GetCoordinates() const;
		const void AddNeighbour(NeighbourInfo* neighbour);
		const bool HasNeighbour(const Piece* piece);
		virtual bool CanRemove();
		void Remove(EventListener* otherHandler);
		void RegisterEvents(EventListener& handler);
		bool IsEmpty();

		bool operator==(const Piece& a) {
			return this->boardPosition->x == a.boardPosition->x && this->boardPosition->y == a.boardPosition->y
				&& this->coordinates->x == a.coordinates->x && this->coordinates->y == a.coordinates->y;
		}

		void operator=(const Piece& rhs);

	protected:
		virtual void Remove();

	private:
		unique_ptr<BoardPosition> boardPosition;
		unique_ptr<Coordinates> coordinates;
		list<NeighbourInfo*> neighbours;

		void RemoveNeighbour(const Piece* piece);
		NeighbourInfo* GetNeighbour(const Piece* piece);
		void RedefineNeighbours();
	};


	class EventPieceRemoved : public Event {
	private:
		const Piece* piece;

	public:
		EventPieceRemoved(const Piece* _piece);
		const Piece& GetPiece() const;
	};
}