#include "sr-wormhole.h"

//Wormhole Class
Wormhole::Wormhole(sf::Vector2f pos, int radius){
  _texture.loadFromFile("./art/wormhole.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  draw = true;
  hasAnimation = false;
  _movable = false;
  setPosition(pos);
  setRadius(radius);
}

void Wormhole::setOpen(bool open){
  _open = open;
}

bool Wormhole::getOpen(){
  return _open;
}