#include "sr-orbitPlanet.h"
#include <iostream>

OrbitPlanet::OrbitPlanet(sf::Vector2f pos, int radius, int gravity) : Planet(pos, radius, gravity) {
	_ellipse = new Ellipse(100,40,100);
	
}