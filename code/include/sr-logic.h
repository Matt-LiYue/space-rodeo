#ifndef SR_LOGIC_H
#define SR_LOGIC_H

#include <SFML/Graphics.hpp>
#include "sr-ship.h"

class Logic {
  public:
		Logic();
		sf::Shape getShipShape();
		
	private:
    Ship _ship;
};

#endif