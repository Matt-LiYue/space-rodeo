#ifndef _SR_ORBIT_PLANET_H_
#define _SR_ORBIT_PLANET_H_

#include <SFML/Graphics.hpp>
#include "sr-planet.h"
#include "sr-ellipse.h"


class OrbitPlanet : public Planet {
  public:
	  OrbitPlanet(sf::Vector2f pos, int radius, int gravity);
	private:
		Ellipse* _ellipse;
};



#endif