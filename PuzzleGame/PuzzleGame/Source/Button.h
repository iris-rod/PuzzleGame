#pragma once
#include "InteractiveObject.h"

class Button : public InteractiveObject {
public:
	Button(const int Id, const int x, const int y, const int _sizeX, const int _sizeY);
	void SetText();
	void SetImage(string image);

private:
	
};
