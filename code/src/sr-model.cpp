#include <SFML/Graphics.hpp>
#include "sr-model.h"
#include <iostream>

//constructor
//Ship class
Ship::Ship(sf::Vector2f pos, int radius, int burst){//Ship is a circle class
  _burst = burst;
  _movable = true;
  setPosition(pos);
  setRadius(radius);
}



//Planet Class
Planet::Planet(sf::Vector2f pos, int radius, int gravity,int cow){
  _cow = cow;
  _movable = false;
  _gravitybound = gravity; 
  setPosition(pos);
  setRadius(radius);
}
int Planet::getCowno(){
  return _cow;
}
//Cow Class

Cow::Cow(sf::Vector2f pos, int radius, Cow::CowType type){
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
//CircleModel - Base Class of Circle-shaped elements
sf::Vector2f CircleModel::getSpd(){
  return _spd;
}

void CircleModel::setSpd(sf::Vector2f speed){
  _spd = speed;
}


//This Models will be in charge of storing all the elements in a map, and providing proper APIs for the VIEW Class to draw the elements.
Models::Models(){//TODO: Read from a txt file to place the elements in map
  _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
  _circlemodels.push_back(new Planet(sf::Vector2f(400,200),60,20,3));
  _circlemodels.push_back(new Cow(sf::Vector2f(300,400),10,Cow::FLY));
  _circlemodels[0] -> setSpd(sf::Vector2f(50,50));

}
std::vector<CircleModel*> Models::getcirmodels(){
  return _circlemodels;
}
