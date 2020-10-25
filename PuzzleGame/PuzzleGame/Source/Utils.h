#pragma once
#include <iostream>
#include <string>


enum class Colors {
	RED,
	GREEN,
	YELLOW,
	BLUE,
	ORANGE,
	EMPTY,
	last
};

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
	case Colors::EMPTY:
		return "empty";
	}
}

static Colors GetRandomColor() {
	return static_cast<Colors>(rand() % (int)Colors::last);
}
