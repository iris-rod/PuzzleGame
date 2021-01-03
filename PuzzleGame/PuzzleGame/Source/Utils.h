#pragma once
#include <iostream>
#include <string>

enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	last
};

enum class Colors {
	RED,
	GREEN,
	YELLOW,
	BLUE,
	ORANGE,
	EMPTY,
	last
};

static Direction ConvertBoardPositionToDirection(int pivot_x, int pivot_y, int x, int y) {
	if (x > pivot_x) return Direction::EAST;
	else if (x < pivot_x) return Direction::WEST;

	if (y > pivot_y) return Direction::SOUTH;
	else if (y < pivot_y) return Direction::NORTH;

}

static std::string ConvertColorToTextureId(Colors color) {
	switch (color) {
	case Colors::BLUE:
		return "blue";
	case Colors::GREEN:
		return "green";
	case Colors::ORANGE:
		return "orange";
	case Colors::RED:
		return "red";
	case Colors::YELLOW:
		return "yellow";
	default:
		return "empty";
	}
}

static Colors GetRandomColor() {
	return static_cast<Colors>(rand() % (int)Colors::EMPTY);
}
