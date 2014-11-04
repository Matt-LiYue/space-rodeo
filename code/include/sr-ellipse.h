#ifndef _SR_ELLIPSE_H_
#define _SR_ELLIPSE_H_

#include <SFML/Graphics.hpp>

class Ellipse : public sf::ConvexShape {
  public:
	  Ellipse(float xRadius, float yRadius, int numPoints);
		float xRad();
		float yRad();
		
  private:
		float _xRad;
		float _yRad;
};



#endif