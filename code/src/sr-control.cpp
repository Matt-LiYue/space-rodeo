#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "sr-control.h"


Control::Control(){
  std::cout << "\nController initialized \n";
}


void Control::setmodels(std::vector<CircleModel*>& mymodels){
  _cirmodels = mymodels;
  ;
}


void Control::update(float timeInterval){
	sf::Vector2f gravityPull;
	
  for (int i = 0; i < _cirmodels.size(); i++){
    if (_cirmodels[i] -> _movable == true) {
			
    	/* update positions */
			if (dynamic_cast<Ship*>(_cirmodels[i]) != 0 && dynamic_cast<Ship*>(_cirmodels[i])->getState() == Ship::ORBIT)
				gravityPull = dynamic_cast<Ship*>(_cirmodels[i])->getGravityPull();
			else
				gravityPull = sf::Vector2f(0,0);
      _cirmodels[i] -> setPosition(_cirmodels[i]->getPosition() + (_cirmodels[i]->getSpd() + gravityPull) * timeInterval);
			
			/* check on map */
		 
			/* check intersections */
			for (int j = 0; j < _cirmodels.size(); j++) {
				if (i == j) continue;

				/* real intersection */
				if (_cirmodels[i]->intersects(_cirmodels[j])) {
					
					if (dynamic_cast<Ship*>(_cirmodels[i]) != 0) {
						std::cout << "ship has hit something\n"; exit(0);
						
						if (dynamic_cast<Cow*>(_cirmodels[j]) != 0) {
							/* handle cow hit */
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
<<<<<<< HEAD
=======
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
	ship -> setOrbit(0);
	ship -> setState(Ship::FLY);
				}
>>>>>>> e1a48c81df092526405118764ff7c84053601cb3
      }
    }
  if (event.key.code == sf::Keyboard::Left){
    if (ship -> getState() == Ship::REST){
      ship -> rotate(-5); 
    }
  }
  if (event.key.code == sf::Keyboard::Right){
    if (ship -> getState() == Ship::REST){
      ship -> rotate(5);
    }
  } 
}
