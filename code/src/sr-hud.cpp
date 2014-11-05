#include "sr-hud.h"
HUD::HUD(){
  _font.loadFromFile("arial.ttf");
  _text.setFont(_font);
  _texture.loadFromFile("cow.png");
  _textpointer = &_texture;
  _icon.setTexture(_textpointer);
  _text.setString("test");
}
void HUD::initialize(int radius, sf::Vector2f pos, int burst, int life, int cow){
  _icon.setRadius(radius);
  _icon.setPosition(pos);
  _text.setPosition(pos + sf::Vector2f(radius*2,0));
  _text.setCharacterSize(radius);
  _burst = burst;
  _life = life;
  _cow = cow;
  _text.setString("hello");
}
int HUD::getcow(){
  return _cow;
}
int HUD::getlife(){
  return _life;
}
int HUD::getburst(){
  return _burst;
}
void HUD::setcow(int cow){
  _cow = cow;
}
void HUD::setlife(int life){
  _life = life;
}
void HUD::setburst(int burst){
  _burst = burst;
}
sf::CircleShape HUD::geticon(){
  return _icon;
}
void HUD::settext(std::string Str){
  _text.setString(Str);
}
sf::Text HUD::gettext(){
  return _text;
}