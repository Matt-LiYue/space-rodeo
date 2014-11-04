#include <iostream>
#include "sr-animation.h"

Animation::Animation() {
	_curFrame = 0;
}

void Animation::setSize(float size) {
	_size = size;
}

void Animation::addFrame(float x1, float x2, float y1, float y2) {	
	_frameCoords.push_back(x1);
	_frameCoords.push_back(x2);
	_frameCoords.push_back(y1);
	_frameCoords.push_back(y2);
}

void Animation::advanceFrame() {
	if (_frameCoords.size() == 0) {
		return;
	}
	_curFrame = (_curFrame + 1) % (_frameCoords.size()/4);
	_setFrame(_curFrame);
}

void Animation::_setFrame(int i) {
	float x1 = _frameCoords[4*i];
	float y1 = _frameCoords[4*i+1];
	float x2 = _frameCoords[4*i+2];
	float y2 = _frameCoords[4*i+3];

	setTextureRect(sf::IntRect(x1,y1,x2,y2));
	setScale(_size/(x2-x1), _size/(y2-y1));
	setOrigin((x2-x1)/2.0, (y2-y1)/2.0);
}