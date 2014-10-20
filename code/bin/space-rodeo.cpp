#include <SFML/Graphics.hpp>
#include <iostream>
#include "sr-view.h"
#include <unistd.h>

int main(int argc, char** argv){
  Models mymodels;
  View myview;
  Control mycontrol;
  myview.setController(mycontrol);
  sf::Time _interval;
  sf::Clock _mainclock;
  while (myview.isRun()){
    _mainclock.restart();
    std::vector<CircleModel*> mycirmodels = mymodels.getcirmodels();
/*
  for (int i = 0; i < mycirmodels.size(); i++)
    std::cout << mycirmodels[i]->getPosition().x << "," << mycirmodels[i]->getPosition().y << "\n";
  mycirmodels[0] -> setPosition(sf::Vector2f(123,321));
  for (int i = 0; i < mycirmodels.size(); i++)
    std::cout << mycirmodels[i]->getPosition().x << "," << mycirmodels[i]->getPosition().y << "\n";
*/
    myview.drawAll(mycirmodels);
    _interval = _mainclock.getElapsedTime();
    mycontrol.setmodels(mycirmodels);
    mycontrol.update(_interval.asSeconds());
  }
  return 0;
}
