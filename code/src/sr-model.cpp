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
}

void Ship::adjustSpd(int spd){//Used for adjust speed for rotation and firing
  float angle = getRotation() - 90;
  std::cout << angle<< "\n";
  setSpd(sf::Vector2f(spd * cos(angle*M_PI/180), spd * sin(angle*M_PI/180)));
}

void Ship::setOrbit(Planet* planet) {
	_orbiting = planet;
	std::cout << "setting orbit" << std::endl;
	setPosition(planet->getPosition());
	setOrigin(sf::Vector2f(getRadius() + planet->getRadius() + 30,getRadius()));
	//sf::Vector2f oldPos = sf::Vector2f(300,300);
	//sf::Vector2f trans = sf::Vector2f(getRadius(),getRadius()) - getOrigin();
	//setOrigin(sf::Vector2f(0,0));
	//setPosition();
        //std::cout << getRotation()<<std::endl;
        //std::cout << planet->getPosition().x << "," << planet->getPosition().y<<std::endl;
	//std::cout << getOrigin().x << "," << getOrigin().y << std::endl;
	//std::cout << getPosition().x << "," << getPosition().y << std::endl;

}

void Ship::quitOrbit(){
  float dis = getOrigin().x - getRadius();
  float angle = getRotation();
  setPosition(getPosition().x-cos(angle*M_PI/180)*dis, getPosition().y-sin(angle*M_PI/180)*dis);
  setOrigin(sf::Vector2f(getRadius(),getRadius()));
  //std::cout << "OUT: "<<getPosition().x << "," << getPosition().y<<std::endl;
}

Planet* Ship::getOrbitPlanet() {
  return _orbiting;	
}

sf::Vector2f Ship::getGravityPull() {
	return _gravityPull;
}

void Ship::setSpd(sf::Vector2f spd){
  _spd = spd;
  adjustOri(spd);
}

void Ship::adjustOri(sf::Vector2f spd){
 ;
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
    _circlemodels.push_back(new Cow(sf::Vector2f(400,300),40,Cow::FLY));
    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,300),70));
  }
  if (level == 1){
    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
    _circlemodels.push_back(new Planet(sf::Vector2f(300,200),70,30,0));
    _circlemodels.push_back(new Cow(sf::Vector2f(600,400),40,Cow::FLY));
    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
  }
   for (int i=0; i<_circlemodels.size(); i++) {
    float r = _circlemodels[i]->getRadius();
    sf::Vector2f center = _circlemodels[i]->getPosition();
    _circlemodels[i]->setOrigin(sf::Vector2f(r,r));
    _circlemodels[i]->setPosition(center);
    std::cout << _circlemodels[i]->getPosition().x << "," << _circlemodels[i]->getPosition().y << std::endl;
    std::cout << _circlemodels[i]->getOrigin().x << "," << _circlemodels[i] -> getOrigin().y<<std::endl;
  }
}
std::vector<CircleModel*> Models::getcirmodels(){
  return _circlemodels;
}

