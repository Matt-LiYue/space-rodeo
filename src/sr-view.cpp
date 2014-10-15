#include "sr-view.h"
#include <iostream> // dbg

View::View(int height, int width, Logic& logic, sf::RenderWindow& window) {
	_height = height;
	_width = width;
	_logic = &logic;
	_window = &window;	
}

void View::drawPlay() {
	sf::Shape* shipShape = _logic->getShipShape();
	shipShape->setPosition(_width * shipShape->getPosition().x, _height * shipShape->getPosition().y);
  _window->draw(*shipShape);	
	
	/* for model in getModels, draw model */
}

/* getModels - gets list/array of models to draw

*/


