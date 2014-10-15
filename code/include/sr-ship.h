#ifndef SR_SHIP_H
#define SR_SHIP_H

#include <SFML/Graphics.hpp>
#include "sr-model.h"

class Ship: public Model {
	public:
		//constructor
	  Ship();
		
		// mutators
		void setPosition(float x, float y);
		
		
		// accessor
		sf::Shape* getShape();
		

};

#endif