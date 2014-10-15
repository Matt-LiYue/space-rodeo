#include "sr-logic.h"
#include <iostream> // dbg

// Constructor
Logic::Logic() {
  srand(time(NULL));
  _ship = Ship();
}

Logic::beginLevel() {
	_ship.setPosition()
}

// Accessors
/*sf::Shape Logic::getShipShape() {
	// should be changed to getShapes - returns a vector of all shapes to draw
	return _ship.getShape();
}
*/
