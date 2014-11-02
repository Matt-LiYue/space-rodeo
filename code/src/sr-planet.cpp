#include "sr-planet.h"

//Planet Class
Planet::Planet(sf::Vector2f pos, int radius, int gravity){
	hasAnimation = false;
  _texture.loadFromFile("planet.png");
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