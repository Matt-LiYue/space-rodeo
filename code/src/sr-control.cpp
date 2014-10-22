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

void Control::handleEvent(sf::Event event){
  if (event.key.code == sf::Keyboard::Space){ // Fire the rocket
    _cirmodels[0] -> setSpd(sf::Vector2f(50,50)); //fire
  }
}


