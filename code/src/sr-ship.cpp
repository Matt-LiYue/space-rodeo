#include "sr-ship.h"

Ship::Ship() 
{
	_shape = sf::CircleShape(50,3);
}

void Ship::setPosition(float x, float y) {
	/* Sets pixel position */
	_xPos = x;
	_yPos = y;
	_shape.setPosition(x,y);
}

sf::Shape Ship::getShape()
{
  return _shape;
}