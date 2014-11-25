#include "sr-orbitPlanet.h"
#include <iostream>

OrbitPlanet::OrbitPlanet(sf::Vector2f center, float xRad, float yRad, int numPoints, float period, int planetRad, int gravity) : 
Planet(sf::Vector2f(center.x + xRad, center.y), planetRad, gravity) {
  
  std::cout << "creating orbit planet\n";
  //_ellipse = new Ellipse(xRad, yRad, numPoints);
  //_ellipse->setOrigin(xRad, yRad);
  //_ellipse->setPosition(center);
  //_star = new Star(center, min(xRad,yRad)/2);
	_xRad = xRad;
	_yRad = yRad;
	_center = center;
  _curTheta = 0;
  _prevTheta = 0;
  _dTime = 0;
  _period = period;
  _angularVelocity = 2 * M_PI / period;
  std::cout << "_angularVelocity: " << _angularVelocity << std::endl;
  
}

void OrbitPlanet::updatePosition(float dTime) {
  float a = _xRad;
  float b = _yRad;
  float dTheta = dTime * _angularVelocity;
  sf::Vector2f oldRelPos = getPosition() - _center;
  float theta = atan2(oldRelPos.y, oldRelPos.x) + dTheta;
  sf::Vector2f newRelPos = sf::Vector2f(a * cos(theta), b * sin(theta));
  _spd = (newRelPos - oldRelPos) / dTime;
  setPosition(dTime * _spd + getPosition());
}

sf::Vector2f OrbitPlanet::getVelocity() {
  return _spd;
}