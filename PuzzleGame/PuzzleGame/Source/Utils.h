#include <iostream>
#include <string>
#include "Ore.h"

enum class Colors {
	RED,
	GREEN,
	YELLOW,
	BLUE,
	ORANGE,
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
	}
}

static Colors GetRandomColor() {
	return static_cast<Colors>(rand() % (int)Colors::last);
}
