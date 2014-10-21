#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "sr-control.h"


Control::Control(){
  std::cout << "\nController initialized \n";
}


void Control::setmodels(std::vector<CircleModel*>& mymodels){
  _cirmodels = mymodels;
}


void Control::update(float timeInterval){
  for (int i = 0; i < _cirmodels.size(); i++){
    if (_cirmodels[i] -> _movable == true) {
			
    	/* update positions */
      _cirmodels[i] -> setPosition(_cirmodels[i] -> getPosition() + _cirmodels[i] -> getSpd()*timeInterval);
			
			/* check on map */
		 
			/* check intersections */
			for (int j = 0; j < _cirmodels.size(); j++) {
				if (i == j) continue;

				/* real intersection */
				if (_cirmodels[i]->intersects(_cirmodels[j])) {
					
					if (dynamic_cast<Ship*>(_cirmodels[i]) != 0) {
						
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
					
					if (ship->intersects(&gravity)) {
						/* check for orbit or crash */
						sf::Vector2f shipToPlanet = planet->getPosition() - ship->getPosition();
						sf::Vector2f dir = ship->getSpd();
						float dot = shipToPlanet.x * dir.x + shipToPlanet.y * dir.y;
						sf::Vector2f secant = (dir * dot / (float) sqrt(dir.x*dir.x + dir.y*dir.y)) - planet->getPosition();
						if (sqrt(secant.x*secant.x + secant.y*secant.y) < planet->getRadius() + ship->getRadius()) {
							/* crash */
						}
						else {
							/* orbit */
						}
					}
				}
			}
		}
  }
	
	
	

}


void Control::handleEvent(sf::Event event){
  //if (event.key.code == sf::Keyboard::Space) // Fire the rocket
 //std::cout << _cirmodels[0] -> getPosition().x; 
}
