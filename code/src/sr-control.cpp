#include <SFML/Graphics.hpp>
#include <iostream>
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
		
			/* check intersections */
			for (int j = 0; j < _cirmodels.size(); j++) {
				if (i == j) continue;
				if (_cirmodels[i]->intersects(_cirmodels[j])) {
				/*
					numLives--;
					if (numLives == 0) gameOver();
				  else restartLevel();
				*/
				}
			}
		}
  }
	
	
	

}


void Control::handleEvent(sf::Event event){
  //if (event.key.code == sf::Keyboard::Space) // Fire the rocket
 //std::cout << _cirmodels[0] -> getPosition().x; 
}
