#include "sr-asteroid.h"

//Asteroid Class
Asteroid::Asteroid(sf::Vector2f pos, int radius, sf::Vector2f spd){
  _texture.loadFromFile("./art/asteroid.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  draw = true;
  hasAnimation = false;
  _movable = true;
  _oripos = pos;
  setPosition(pos);
  setRadius(radius);
  setSpd(spd);
  setExist(true);
}

void Asteroid::replay(){
  setPosition(_oripos);
  setExist(true);
}

void Asteroid::setExist(bool exist){
  _exist = exist;
}

bool Asteroid::getExist(){
  return _exist;
}

