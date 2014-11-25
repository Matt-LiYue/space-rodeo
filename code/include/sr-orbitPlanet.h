#ifndef _SR_ORBIT_PLANET_H_
#define _SR_ORBIT_PLANET_H_

#include <SFML/Graphics.hpp>
#include "sr-planet.h"

class OrbitPlanet : public Planet {
  public:
	  OrbitPlanet(sf::Vector2f center, float xRad, float yRad, int numPoints, float period, int planetRad, int gravity);
		void updatePosition(float dTime);
		sf::Vector2f getVelocity();
	private:
		//Ellipse* _ellipse;
		sf::Vector2f _center;
		float _xRad;
		float _yRad;
		float _period;
		float _curTheta;
		float _prevTheta;
		float _dTime;
		float _angularVelocity;

};



#endif