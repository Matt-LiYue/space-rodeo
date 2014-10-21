#include <SFML/Graphics.hpp>
#include <iostream>
#include "sr-view.h"
#include <unistd.h>

int main(int argc, char** argv){
  Models mymodels;
  View myview;
  Control mycontrol;
  sf::Time _interval;
  sf::Clock _mainclock;
  std::vector<CircleModel*> mycirmodels = mymodels.getcirmodels();
  mycontrol.setmodels(mycirmodels);
  myview.setController(mycontrol);
  while (myview.isRun()){
    _mainclock.restart();
    myview.drawAll(mycirmodels);
    _interval = _mainclock.getElapsedTime();
    mycontrol.update(_interval.asSeconds());
  }
  return 0;
}
