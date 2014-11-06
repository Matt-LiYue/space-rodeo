#include "sr-hud.h"
HUD::HUD(){
  _font.loadFromFile("arial.ttf");
  _text.setFont(_font);
  _cowtexture.loadFromFile("cow.png");
  _cowicon.setTexture(&_cowtexture);
  _bursttexture.loadFromFile("burst.png");
  _bursticon.setTexture(&_bursttexture);
  _lifetexture.loadFromFile("rock.png");
  _lifeicon.setTexture(&_lifetexture);
  _text.setString("test\ntest\ntest");
}
void HUD::initialize(int radius, sf::Vector2f pos, int burst, int life, int cow){
  _cowicon.setRadius(radius);
  _cowicon.setPosition(pos);
  _bursticon.setRadius(radius);
  _bursticon.setPosition(pos + sf::Vector2f(0,radius*2));
  _lifeicon.setRadius(radius);
  _lifeicon.setPosition(pos + sf::Vector2f(0,radius*4));
  _text.setPosition(pos + sf::Vector2f(radius*2,0));
  _text.setCharacterSize(radius*1.5);
  _burst = burst;
  _life = life;
  _cow = cow;
  _text.setString("test\ntest\ntest");
}

void HUD::update(){
  char outstr[100];
  sprintf(outstr, " X %d\n X %d\n X %d \n", _cow,_burst,_life);
  _text.setString(outstr);
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
sf::CircleShape HUD::getcowicon(){
  return _cowicon;
}
sf::CircleShape HUD::getbursticon(){
  return _bursticon;
}
sf::CircleShape HUD::getlifeicon(){
  return _lifeicon;
}
void HUD::settext(std::string Str){
  _text.setString(Str);
}
sf::Text HUD::gettext(){
  return _text;
}