#include "sr-orbitPlanet.h"
#include <iostream>

OrbitPlanet::OrbitPlanet(sf::Vector2f center, float xRad, float yRad, int numPoints, float period, int planetRad, int gravity) : 
	Planet(sf::Vector2f(center.x + xRad, center.y), planetRad, gravity) {
		
		std::cout << "creating orbit planet\n";
	_ellipse = new Ellipse(xRad, yRad, numPoints);
	_ellipse->setOrigin(xRad, yRad);
	_ellipse->setPosition(center);
  //_star = new Star(center, min(xRad,yRad)/2);

	_curTheta = 0;
	_prevTheta = 0;
	_dTime = 0;
	_period = period;
	_angularVelocity = 2 * M_PI / period;
	std::cout << "_angularVelocity: " << _angularVelocity << std::endl;
	
}

void OrbitPlanet::updatePosition(float dTime) {
	/*_prevTheta = _curTheta;
	_dTime = dTime;
	_curTheta += dTime / _period * 2 * M_PI;
	sf::Vector2f elCoord = sf::Vector2f(_ellipse->xRad() * cos(_curTheta), _ellipse->yRad() * sin(_curTheta));
	setPosition(elCoord + _ellipse->getPosition());
	*/
	float a = _ellipse->xRad();
	float b = _ellipse->yRad();
	float dTheta = dTime * _angularVelocity;
	sf::Vector2f oldRelPos = getPosition() - _ellipse->getPosition();
	
	float theta = atan2(oldRelPos.y, oldRelPos.x) + dTheta;
  sf::Vector2f newRelPos = sf::Vector2f(a * cos(theta), b * sin(theta));
	//std::cout << "dTheta: " << dTheta << std::endl;
	//std::cout << "theta: " << theta << std::endl;
	//std::cout << "relPos: " << newRelPos.x << "," << newRelPos.y << std::endl;
	
	_spd = (newRelPos - oldRelPos) / dTime;
	setPosition(dTime * _spd + getPosition());
	//setPosition(newRelPos + _ellipse->getPosition());
}

sf::Vector2f OrbitPlanet::getVelocity() {
	/*float a = _ellipse->xRad();
	float b = _ellipse->yRad();
	float x = a * (cos(_curTheta) - cos(_prevTheta));
	float y = b * (sin(_curTheta) - sin(_prevTheta));
	return sf::Vector2f(x,y);
	*/
	return _spd;
}