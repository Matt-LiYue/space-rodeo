#include "sr-spaceRanch.h"

//SpaceRanch Class
SpaceRanch::SpaceRanch(sf::Vector2f pos, int radius){
  _texture.loadFromFile("ranch.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
	draw = true;
	hasAnimation = false;
  _movable = false;
  setPosition(pos);
  setRadius(radius);
}