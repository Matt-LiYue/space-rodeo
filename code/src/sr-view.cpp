#include <SFML/Graphics.hpp>
#include "sr-view.h"
#include <iostream>

View::View(){
  _view.create(sf::VideoMode(800,600,32),"Space Rodeo");
  std::cout << _view.isOpen();
}

void View::drawAll(std::vector<CircleModel*> mycirmodels){
  _view.clear(sf::Color::Black);
  while (_view.pollEvent(_event)){//TODO: Use Control Class to handle the event
    if (_event.type == sf::Event::Closed)
      _view.close();
  }
  for (int i = 0; i < mycirmodels.size(); i++){
    _view.draw(*mycirmodels[i]);
  }
  _view.display();
}

bool View::isRun(){
  if (_view.isOpen())
    return true;
  else
    return false;
}
