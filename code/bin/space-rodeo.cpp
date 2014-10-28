#include <SFML/Graphics.hpp>
#include <iostream>
#include "sr-view.h"
#include <unistd.h>

int main(int argc, char** argv){
  for (int i = 0 ; i < 2; i++){
  Models mymodels(i);
  View myview;
  Control mycontrol;
  sf::Time _interval;
  sf::Clock _mainclock;
  std::vector<CircleModel*> mycirmodels = mymodels.getcirmodels();
	std::cout << mycirmodels.size() << std::endl;
  mycontrol.setmodels(mycirmodels);
	std::cout << mycirmodels.size() << std::endl;
	
  myview.setController(mycontrol);
  while (myview.isRun()){
    _mainclock.restart();
    myview.drawAll(mycirmodels);
    _interval = _mainclock.getElapsedTime();
    mycontrol.update(_interval.asSeconds());
    if (mycontrol.getlevelfinished() == true) break;
  }
  }
  return 0;
}
