#include "Button.h"

Button::Button(const int Id, const int x, const int y, const int _sizeX, const int _sizeY) :
	InteractiveObject( "button" + Id, x, y, _sizeX, _sizeY) {

}

void Button::SetImage(string image) {
	textureId = image;
}

