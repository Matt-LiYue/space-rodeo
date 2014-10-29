#include <SFML/Graphics.hpp>
#include <math.h> /* fabs */
#include "sr-model.h"
#include "sr-utils.h"
#include <iostream>

//Ship class
Ship::Ship(sf::Vector2f pos, int radius, int burst){//Ship is a circle class
  _texture.loadFromFile("rock.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  _burst = burst;
	_lasso = new Lasso(20,100);
  _movable = true;
	draw = true;
  _shipState = Ship::REST;
  setPosition(pos);
  setRadius(radius);
  setOrigin(radius,radius);//for ship rotation
  rotate(90);
	
}

int Ship::getburst(){
  return _burst;
}

Ship::ShipState Ship::getState(){
  return _shipState;
}

void Ship::setState(Ship::ShipState state){
  _shipState = state;
	std::cout << "setting state: " << state << std::endl;
}

void Ship::adjustSpd(int spd){//Used for adjust speed for rotation and firing
  float angle = getDir();
  setSpd(sf::Vector2f(spd * cos(angle*M_PI/180), spd * sin(angle*M_PI/180)));
}

void Ship::setOrbit(Planet* planet) {
	_orbiting = planet;
}

float Ship::getDir() { return getRotation() - 90;}

Planet* Ship::getOrbitPlanet() {
  return _orbiting;	
}

void Ship::setAngularVelocity(float av) {
	_angularVelocity = av;
}

float Ship::getAngularVelocity() {
	return _angularVelocity;
}

void Ship::setSpd(sf::Vector2f spd){
  _spd = spd;
  adjustOri(spd);
}

void Ship::adjustOri(sf::Vector2f spd){
 ;
}

Lasso* Ship::getLasso() {return _lasso;}
sf::Vector2f Ship::getLassoDest() {return _lassoDest; }

void Ship::shoot() {
	float offset = getRadius()+_lasso->getRadius();
	sf::Vector2f dir = sf::Vector2f(cos(getDir()* M_PI/180),sin(getDir()* M_PI / 180)) ;
	_lasso->setSpd(dir * _lasso->getLassoSpd());
	_lasso->setPosition(getPosition() + dir * offset);
	_lassoDest = sf::Vector2f(_lasso->getPosition() + dir * _lasso->getLength());
	_lasso->draw = true;
	_lasso->setState(Lasso::SHOT);
}


//Planet Class
Planet::Planet(sf::Vector2f pos, int radius, int gravity,int cow){
  _texture.loadFromFile("planet.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
  _cow = cow;
	draw = true;
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
	draw = true;
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
	draw = true;
  _movable = false;
  setPosition(pos);
  setRadius(radius);
}

// Lasso Class
Lasso::Lasso(int radius, float length) {
  _texture.loadFromFile("art/lasso_3.png");
  _textpointer = &_texture;
  setTexture(_textpointer);
	draw = false;
	_movable = true;
	_length = length;
  setRadius(radius);
	setPosition(-500,-500);
	_lassoSpd = 300;
}

Lasso::LassoState Lasso::getState(){
  return _lassoState;
}

float Lasso::getLength() { return _length; }
float Lasso::getLassoSpd() { return _lassoSpd; }

void Lasso::setState(LassoState state){
  _lassoState = state;
	std::cout << "setting state: " << state << std::endl;
}

//float Lasso::getSpd() { return _spd; }
//void Lasso::setSpd(spd) { _spd = spd; }

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
Models::Models(int level){//TODO: Read from a txt file to place the elements in map
  if (level == 0){
    _circlemodels.push_back(new Ship(sf::Vector2f(50,300), 20, 5));
		_circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
    _circlemodels.push_back(new Cow(sf::Vector2f(400,300),40,Cow::FLY));
    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,300),70));
  }
  if (level == 1){
    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
		_circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
    _circlemodels.push_back(new Planet(sf::Vector2f(300,200),70,30,0));
    _circlemodels.push_back(new Cow(sf::Vector2f(600,400),40,Cow::FLY));
		_circlemodels.push_back(new Cow(sf::Vector2f(500,200),40,Cow::FLY));
    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
  }
	std::cout << "Original models: " << _circlemodels.size() << std::endl;
  for (int i=0; i<_circlemodels.size(); i++) {
    float r = _circlemodels[i]->getRadius();
    sf::Vector2f center = _circlemodels[i]->getPosition();
    _circlemodels[i]->setOrigin(sf::Vector2f(r,r));
    _circlemodels[i]->setPosition(center);
  }
}
std::vector<CircleModel*> Models::getcirmodels(){
  return _circlemodels;
}

