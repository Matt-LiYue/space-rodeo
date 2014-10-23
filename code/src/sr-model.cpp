#include <SFML/Graphics.hpp>
#include <math.h> /* fabs */
#include "sr-model.h"
#include <iostream>

//Ship class
Ship::Ship(sf::Vector2f pos, int radius, int burst){//Ship is a circle class
  _texture.loadFromFile("rock.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  _burst = burst;
  _movable = true;
  _shipState = Ship::REST;
  setPosition(pos);
  setRadius(radius);
  setOrigin(radius,radius);//for ship rotation
}

int Ship::getburst(){
  return _burst;
}

Ship::ShipState Ship::getState(){
  return _shipState;
}

void Ship::setState(Ship::ShipState state){
  _shipState = state;
}

void Ship::adjustSpd(int spd){//Used for adjust speed for rotation and firing
  float angle = getRotation();
  float PI = 3.1415926;
  std::cout << angle<< "\n";
  setSpd(sf::Vector2f(spd * cos(angle*PI/180), spd * sin(angle*PI/180)));
}

void Ship::setOrbit(Planet* planet) {
	_orbiting = planet;

}

sf::Vector2f Ship::getGravityPull() {
	return _gravityPull;
}


//Planet Class
Planet::Planet(sf::Vector2f pos, int radius, int gravity,int cow){
  _texture.loadFromFile("planet.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  _cow = cow;
  _movable = false;
  _gravitybound = gravity; 
  setPosition(pos);
  setRadius(radius);
}
int Planet::getCowno(){
  return _cow;
}

sf::CircleShape Planet::getGravityCircle() {
	sf::CircleShape cs = sf::CircleShape(_gravitybound + getRadius());
	cs.setPosition(getPosition());
	return cs;
}


//Cow Class
Cow::Cow(sf::Vector2f pos, int radius, Cow::CowType type){
  _texture.loadFromFile("cow.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  _movable = false;
  _cowType = type;
  setPosition(pos);
  setRadius(radius);
}
Cow::CowType Cow::getCowType(){
  return _cowType;
}

int Cow::getCowValue(){
  if (_cowType == FLY)
    return 200;
  else
    return 100;
}

//SpaceRanch Class
SpaceRanch::SpaceRanch(sf::Vector2f pos, int radius){
  _texture.loadFromFile("ranch.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  _movable = false;
  setPosition(pos);
  setRadius(radius);
}

//CircleModel - Base Class of Circle-shaped elements
sf::Vector2f CircleModel::getSpd(){
  return _spd;
}

void CircleModel::setSpd(sf::Vector2f speed){
  _spd = speed;
}

bool CircleModel::intersects(sf::CircleShape *other) {
	sf::Vector2f diff = getPosition() - other->getPosition();
	float radiusSum = getRadius() + other->getRadius();
	if (radiusSum < fabs(diff.x) || radiusSum < fabs(diff.y)) return false;
	if (radiusSum * radiusSum < diff.x*diff.x + diff.y*diff.y) return false;
	return true;
}

//This Models will be in charge of storing all the elements in a map, and providing proper APIs for the VIEW Class to draw the elements.
Models::Models(){//TODO: Read from a txt file to place the elements in map
  _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
  _circlemodels.push_back(new Planet(sf::Vector2f(300,200),60,50,3));
  _circlemodels.push_back(new Cow(sf::Vector2f(300,400),40,Cow::FLY));
  _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,80),50));
	for (int i=0; i<_circlemodels.size(); i++) {
		float r = _circlemodels[i]->getRadius();
		sf::Vector2f center = _circlemodels[i]->getPosition();
		_circlemodels[i]->setOrigin(sf::Vector2f(r,r));
		_circlemodels[i]->setPosition(center);
		std::cout << _circlemodels[i]->getPosition().x << "," << _circlemodels[i]->getPosition().y << std::endl;
	}
}
std::vector<CircleModel*> Models::getcirmodels(){
  return _circlemodels;
}

