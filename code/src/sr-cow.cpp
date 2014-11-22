#include "sr-cow.h"

//Cow Class
Cow::Cow(sf::Vector2f pos, int radius) {
  _texture.loadFromFile("./art/cow.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
	draw = true;
	hasAnimation = false;
  _movable = false;
  setPosition(pos);
  setRadius(radius);
}


