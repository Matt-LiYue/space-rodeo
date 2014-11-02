#include "sr-lasso.h"

// Lasso Class
Lasso::Lasso(int radius, float length) {
	
	hasAnimation = true;
	draw = false;
	_movable = true;
	_length = length;
  setRadius(radius);
	_lassoSpd = 300;
	
  _texture.loadFromFile("art/lasso.png");
	_animation.setSize(radius*2);
	_animation.setTexture(_texture);
	_animation.addFrame(0,0,160,145);
	_animation.addFrame(160,0,305,160);
	_animation.addFrame(0,140,160,300);
}

Lasso::LassoState Lasso::getState() {
  return _lassoState;
}

float Lasso::getLength() { return _length; }

float Lasso::getLassoSpd() { return _lassoSpd; }

void Lasso::setState(LassoState state) {
  _lassoState = state;
}
