#include "sr-logic.h"
#include <iostream> // dbg

// Constructor
Logic::Logic() {
  srand(time(NULL));
  _ship = Ship();
}

void Logic::beginLevel() {
	_ship.setPosition(.01, .5);
}

// Accessors
sf::Shape* Logic::getShipShape() {
	// should be changed to getShapes - returns a vector of all shapes to draw
	return _ship.getShape();
}

