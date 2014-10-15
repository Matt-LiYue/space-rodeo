#ifndef SR_MODEL_H
#define SR_MODEL_H

#include <SFML/Graphics.hpp>

class Model {
  public:
	  //getShape
	
	protected:
		sf::Shape *_shape;
		float _xPos;
		float _yPos;
		
		//void setPosition(float x, float y);
		//sf::Shape getShape();
};

#endif