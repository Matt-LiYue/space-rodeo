#include <iostream>
#include "sr-animation.h"

Animation::Animation() {
	_curFrame = 0;
}

void Animation::setSize(float size) {
	_size = size;
}

void Animation::addFrame(int x1, int y1, int dx, int dy) {	
	_frameCoords.push_back(x1);
	_frameCoords.push_back(y1);
	_frameCoords.push_back(dx);
	_frameCoords.push_back(dy);
}

void Animation::advanceFrame() {
	if (_frameCoords.size() == 0) {
		return;
	}
	_curFrame = (_curFrame + 1) % (_frameCoords.size()/4);
	setFrame(_curFrame);
}

void Animation::setFrame(int i) {
	int x1 = _frameCoords[4*i];
	int y1 = _frameCoords[4*i+1];
	int dx = _frameCoords[4*i+2];
	int dy = _frameCoords[4*i+3];
	
	setTextureRect(sf::IntRect(x1, y1, dx, dy));
	setScale(_size/dx, _size/dy);
	setOrigin(dx/2.0, dy/2.0);
}