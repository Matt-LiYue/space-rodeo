#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "sr-control.h"
#include "sr-utils.h"


Control::Control(){
  _levelfinished = false;
  std::cout << "\nController initialized \n";
}


void Control::setmodels(std::vector<CircleModel*>& mymodels){
  _cirmodels = mymodels;
	
	/* Store circle models as their derived classes */
  for (int i = 0; i < _cirmodels.size(); i++) {
	  if (dynamic_cast<Ship*>(_cirmodels[i]) != 0) {
			_ship = (Ship*) _cirmodels[i];
			_cirmodels.push_back(_ship->getLasso());
		}
	  else if (dynamic_cast<SpaceRanch*>(_cirmodels[i]) != 0)
			_ranch = (SpaceRanch*) _cirmodels[i];
	  else if (dynamic_cast<Planet*>(_cirmodels[i]) != 0)
			_planets.push_back((Planet*) _cirmodels[i]);
	  else if (dynamic_cast<Cow*>(_cirmodels[i]) != 0)
			_cows.push_back((Cow*) _cirmodels[i]);
	}
	std::cout << "number of models: " << _cirmodels.size() << std::endl;
}

bool Control::getlevelfinished(){
  return _levelfinished;
}

void Control::update(float timeInterval) {
	
	/* begin ship movement */
	
	/* Ship States 
	1 - not in a gravity field: state = FLY, _orbiting = 0
	2 - in a gravity field, not yet orbiting: state = GRAVITY, _orbiting = planet*
	3 - in orbit: state = ORBIT, _orbiting = planet*
	4 - has burst out of orbit, still in gravity field: state = BURST, _orbiting = planet*
	5 - not in a gravity field: state = FLY, _orbiting = 0
	*/
	
	Planet* planet = _ship->getOrbitPlanet();
        _ship->decelerate();
	
	/* map exit */
	sf::Vector2f pos = _ship->getPosition();
  if (pos.x < 0 || pos.y < 0 || pos.x > 800 || pos.y > 600) {std::cout << "screen exit\n"; exit(0);}
	
	/* movement */
	if (_ship->getState() == Ship::GRAVITY && 
	  (dot(_ship->getOrbitPlanet()->getPosition() - _ship->getPosition(),_ship->getSpd()) <= 0)) {
		_ship->setState(Ship::ORBIT);
		float theta = sqrt(norm_sqrd(_ship->getSpd()) / norm_sqrd(planet->getPosition() - _ship->getPosition()));
		if (dot(planet->getPosition() - _ship->getPosition(), sf::Vector2f(0,1)) < 1) theta *= -1;
		_ship->setAngularVelocity(theta);
	  	
	}
	
	if (_ship->getState() == Ship::ORBIT) {
	  _ship->setSpd((planet->getPosition() - _ship->getPosition() + rotate(_ship->getPosition() 
			- planet->getPosition(), timeInterval * _ship->getAngularVelocity())) / timeInterval);
		_ship->setPosition(_ship->getPosition() + _ship->getSpd() * timeInterval);
	}
  else {
    _ship->setPosition(_ship->getPosition() + _ship->getSpd() * timeInterval);
	}
	
	/* collisions */
	for (int j=0; j < _cows.size(); j++) {
	  Cow* cow = _cows[j];
		if (_ship->intersects(cow)) {
			cow->draw = false; //TODO: better hit cow status
		}
	}
	
	if (_ship->intersects(_ranch)) {
    std::cout << "space ranch reached" << std::endl;
    _levelfinished = true;
  }
	
	// planet, gravity intersections
	for (int j=0; j < _planets.size(); j++) {
		Planet* planet = _planets[j];
		
		// planet
		if (_ship->intersects(planet)) {
			std::cout << "ship hit planet\n";
			exit(1);
		}
		
		// gravity field
    sf::CircleShape gravity = planet->getGravityCircle();
    if (_ship->getState() == Ship::FLY && _ship->intersects(&gravity)) {
		  _ship->setState(Ship::GRAVITY);
			_ship->setOrbit(planet);
    }
		else if (_ship->getState() == Ship::BURST && !_ship->intersects(&gravity)) {
			_ship->setState(Ship::FLY);
			_ship->setOrbit(0);
		}
		
	}
	/* end ship movement */
	
	/* lasso */
	if (_ship->getLasso()->getState() != Lasso::HELD) {
		Lasso* lasso = _ship->getLasso();
		lasso->setPosition(lasso->getPosition() + lasso->getSpd() * timeInterval);
		if (lasso->getState() == Lasso::SHOT) {
			sf::Vector2f dest = _ship->getLassoDest();
			float r = lasso->getRadius();
				
			/* cow intersect */
			for (int j=0; j < _cows.size(); j++) {
			  Cow* cow = _cows[j];
				if (lasso->intersects(cow)) {
					cow->draw = false; //TODO: better hit cow status
					lasso->setState(Lasso::CAUGHT);
				}
			}
			
			/* destination intersect (point-circle)*/
			if (lasso->getState() != Lasso::CAUGHT &&
				withinBox(lasso->getPosition(), dest.x - r, dest.x + r, dest.y - r, dest.y + r)) {
				if (norm_sqrd(lasso->getPosition() - dest) < r*r) {
					lasso->setState(Lasso::MISSED);
				}
			}
		}
		else if (lasso->getState() == Lasso::CAUGHT || lasso->getState() == Lasso::MISSED) {			
			sf::Vector2f dir = _ship->getPosition() - lasso->getPosition(); // not normalized
			float d_sqrd = norm_sqrd(dir);
			if (d_sqrd < _ship->getRadius() * _ship->getRadius()) {
				lasso->setState(Lasso::HELD);
				lasso->draw = false;
			}
			lasso->setSpd(dir / norm(dir) * lasso->getLassoSpd());
		}
  }
}
	
void Control::handleEvent(sf::Event event){
  if (event.key.code == sf::Keyboard::Space) {
  	_ship->shoot();
  }

  if (event.key.code == sf::Keyboard::Up){ // Fire the rocket
      if (_ship -> getState() == Ship::REST){//fire
        _ship -> adjustSpd(100);
        _ship -> setState(Ship::FLY);
      }
      else if (_ship -> getState() == Ship::FLY){//burst, TODO: Need a counter
        _ship -> adjustSpd(300);
        _ship -> setState(Ship::BURST);
      }
      else if (_ship -> getState() == Ship::ORBIT) {
        _ship -> adjustSpd(300);
	_ship -> setState(Ship::BURST);
      }
  }
  if (event.key.code == sf::Keyboard::Left){
    if (_ship -> getState() == Ship::REST){
      _ship -> rotate(-3); 
    }
  }
  if (event.key.code == sf::Keyboard::Right){
    if (_ship -> getState() == Ship::REST){
      _ship -> rotate(3);
    }
  } 
}
