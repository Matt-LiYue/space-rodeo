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
}

bool Control::getlevelfinished(){
  return _levelfinished;
}

void Control::update(float timeInterval){
	sf::Vector2f gravityPull;
	
  for (int i = 0; i < _cirmodels.size(); i++){
    if (_cirmodels[i] -> _movable == true) {
    	/* update positions */
      if ((dynamic_cast<Ship*>(_cirmodels[i]) != 0) && (dynamic_cast<Ship*>(_cirmodels[i])->getState() == Ship::ORBIT)) {
        Ship* ship = (Ship*) _cirmodels[i];
        Planet* planet = ship->getOrbitPlanet();
        float distance = sqrt(ship->getSpd().x*ship->getSpd().x + ship->getSpd().y*ship->getSpd().y) * timeInterval;
        float theta = 360 * distance / (2 * M_PI * planet->getRadius());
        ship->rotate(theta);
      }
      else {
        _cirmodels[i] -> setPosition(_cirmodels[i]->getPosition() + _cirmodels[i]->getSpd() * timeInterval);
      }	
      /* check on map */
      if (dynamic_cast<Ship*>(_cirmodels[i]) != 0) {
        Ship* ship = (Ship*) _cirmodels[i];
        sf::Vector2f pos = ship->getPosition();
        if (pos.x < 0 || pos.y < 0 || pos.x > 800 || pos.y > 600) exit(0);
      }		 
      /* check intersections */
      for (int j = 0; j < _cirmodels.size(); j++) {
        if (i == j) continue;
      /* real intersection */
        if (_cirmodels[i]->intersects(_cirmodels[j]) && dynamic_cast<Ship*>(_cirmodels[i])->getState() != Ship::ORBIT) {//no hit when orbiting
          if (dynamic_cast<Ship*>(_cirmodels[i]) != 0) {
            if (dynamic_cast<Ship*>(_cirmodels[i])->getState() == Ship::CRASH) exit(0);
	    //std::cout << "ship has hit something\n"; 
            if (dynamic_cast<Cow*>(_cirmodels[j]) != 0) {
              /* handle cow hit */
              //std::cout << "hit cow" << std::endl;
              _cirmodels[j]->draw = false; ; // temp erase
            }	
            else if (dynamic_cast<SpaceRanch*>(_cirmodels[j]) != 0) {
              std::cout << "space ranch reached" << std::endl;
              _levelfinished = true;
            }
          }
					
				/*
					numLives--;
					if (numLives == 0) gameOver();
				  else restartLevel();
				*/
        }
				
        /* gravity intersection */
          if (dynamic_cast<Ship*>(_cirmodels[i]) != 0 && dynamic_cast<Planet*>(_cirmodels[j]) != 0) {
            Planet* planet = (Planet*) _cirmodels[j];
            Ship* ship = (Ship*) _cirmodels[i];
            sf::CircleShape gravity = planet->getGravityCircle();
            if (ship->getState() == Ship::FLY && ship->intersects(&gravity)) {
           /* check for orbit or crash */
              sf::Vector2f shipToPlanet = planet->getPosition() - ship->getPosition();
              sf::Vector2f dir = ship->getSpd();
              float dot = shipToPlanet.x * dir.x + shipToPlanet.y * dir.y;
              sf::Vector2f projection = dir * (dot / (dir.x*dir.x + dir.y*dir.y));
              sf::Vector2f secant = projection + ship->getPosition() - planet->getPosition();
						
						/* dbg
						std::cout << "Planet: " << planet->getPosition().x << "," << planet->getPosition().y << std::endl;
						std::cout << "Ship: " << ship->getPosition().x << "," << ship->getPosition().y << std::endl;
						std::cout << "Dir: " << dir.x << "," << dir.y << std::endl;
						std::cout << "Ship2Planet: " << shipToPlanet.x << "," << shipToPlanet.y << std::endl;
						std::cout << "dot: " << dot << std::endl;
						std::cout << "projection: " << projection.x << "," << projection.y << std::endl;
						std::cout << "secant: " << secant.x << "," << secant.y << std::endl;
						*/
              if (sqrt(secant.x*secant.x + secant.y*secant.y) < planet->getRadius() + ship->getRadius()) {
              /* crash */
                std::cout << "ship will crash into planet\n";
                ship -> setState(Ship::CRASH);
              }
              else {
              /* orbit */
                std::cout << "ship in orbit. state: " << ship -> getState() << "\n";
                ship -> setState(Ship::ORBIT);
                ship -> setOrbit(planet);
              }
            }
            else if (ship->getState() == Ship::ORBIT) { 
            /* Don't perform any gravity intersection calculations */
            }
          } 
        }
    } 
  }
}


void Control::handleEvent(sf::Event event){
  Ship * ship;
  for (int i = 0 ; i < _cirmodels.size(); i++ ){
    if (dynamic_cast<Ship*>(_cirmodels[i]) != 0){ 
      ship = (Ship *) _cirmodels[i];
    }
  }
  if (event.key.code == sf::Keyboard::Space){ // Fire the rocket
      if (ship -> getState() == Ship::REST){//fire
        ship -> adjustSpd(100);
        ship -> setState(Ship::FLY);
      }
      else if (ship -> getState() == Ship::FLY){//burst, TODO: Need a counter
        ship -> adjustSpd(300);
        ship -> setState(Ship::BURST);
      }
      else if (ship -> getState() == Ship::ORBIT) {
        ship -> adjustSpd(300);
        ship -> quitOrbit();
	ship -> setState(Ship::BURST);
      }
  }
  if (event.key.code == sf::Keyboard::Left){
    if (ship -> getState() == Ship::REST){
      ship -> rotate(-3); 
    }
  }
  if (event.key.code == sf::Keyboard::Right){
    if (ship -> getState() == Ship::REST){
      ship -> rotate(3);
    }
  } 
}
