#include "sr-planet.h"

//Planet Class
Planet::Planet(sf::Vector2f pos, int radius, int gravity){
  /* tweakable */  
	_gravMag = 1;
	
  hasAnimation = false;
  _texture.loadFromFile("./art/planet.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  draw = true;
  _movable = false;
  _gravitybound = gravity; 
  setPosition(pos);
  setRadius(radius);
}

sf::CircleShape Planet::getGravityCircle() {
  sf::CircleShape cs = sf::CircleShape(_gravitybound + getRadius());
  cs.setPosition(getPosition());
  return cs;
}

sf::Vector2f Planet::getVelocity() {
  return sf::Vector2f(0,0);
}

float Planet::getGravMag() { return _gravMag; }