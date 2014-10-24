#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "sr-control.h"


Control::Control(){
  _levelfinished = false;
  std::cout << "\nController initialized \n";
}


void Control::setmodels(std::vector<CircleModel*>& mymodels){
  _cirmodels = mymodels;
	
	/* Store circle models as their derived classes */
  for (int i = 0; i < _cirmodels.size(); i++) {
	  if (dynamic_cast<Ship*>(_cirmodels[i]) != 0)
			_ship = (Ship*) _cirmodels[i];
	  else if (dynamic_cast<SpaceRanch*>(_cirmodels[i]) != 0)
			_ranch = (SpaceRanch*) _cirmodels[i];
	  else if (dynamic_cast<Planet*>(_cirmodels[i]) != 0)
			_planets.push_back((Planet*) _cirmodels[i]);
	  else if (dynamic_cast<Cow*>(_cirmodels[i]) != 0)
			_cows.push_back((Cow*) _cirmodels[i]);
	}
}

bool Control::getlevelfinished(){
  return _levelfinished;
}

void Control::update(float timeInterval) {
	
	/* Ship */
	/* map exit */
	sf::Vector2f pos = _ship->getPosition();
  if (pos.x < 0 || pos.y < 0 || pos.x > 800 || pos.y > 600) exit(0);
	
	/* movement */
	if (_ship->getState() == Ship::ORBIT) {
    Planet* planet = _ship->getOrbitPlanet();
    float distance = sqrt(_ship->getSpd().x*_ship->getSpd().x + _ship->getSpd().y*_ship->getSpd().y) * timeInterval;
    float theta = 360 * distance / (2 * M_PI * planet->getRadius());
    _ship->rotate(theta);
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
	
	for (int j=0; j < _planets.size(); j++) {
		Planet* planet = _planets[j];
		if (_ship->getState() == Ship::ORBIT) break; // don't bother w/ collisions if snapped to orbit
    sf::CircleShape gravity = planet->getGravityCircle();
    if (_ship->getState() == Ship::FLY && _ship->intersects(&gravity)) {
			
      /* check for orbit or crash */
      sf::Vector2f shipToPlanet = planet->getPosition() - _ship->getPosition();
      sf::Vector2f dir = _ship->getSpd();
      float dot = shipToPlanet.x * dir.x + shipToPlanet.y * dir.y;
      sf::Vector2f projection = dir * (dot / (dir.x*dir.x + dir.y*dir.y));
      sf::Vector2f secant = projection + _ship->getPosition() - planet->getPosition();
		

      if (sqrt(secant.x*secant.x + secant.y*secant.y) < planet->getRadius() + _ship->getRadius()) {
      /* crash */
        std::cout << "ship will crash into planet\n";
        _ship -> setState(Ship::CRASH);
      }
      else {
      /* orbit */
        std::cout << "ship in orbit. state: " << _ship -> getState() << "\n";
        _ship -> setState(Ship::ORBIT);
        _ship -> setOrbit(planet);
      }
    }
	}
}
	
void Control::handleEvent(sf::Event event){

  if (event.key.code == sf::Keyboard::Space){ // Fire the rocket
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
        _ship -> quitOrbit();
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
