#include <SFML/Graphics.hpp>
#include <iostream>
#include "sr-view.h"
#include <unistd.h>

int main(int argc, char** argv){
  Models mymodels;
  View myview;
  while (myview.isRun()){
    std::vector<CircleModel*> mycirmodels = mymodels.getcirmodels();
/*
  for (int i = 0; i < mycirmodels.size(); i++)
    std::cout << mycirmodels[i]->getPosition().x << "," << mycirmodels[i]->getPosition().y << "\n";
  mycirmodels[0] -> setPosition(sf::Vector2f(123,321));
  for (int i = 0; i < mycirmodels.size(); i++)
    std::cout << mycirmodels[i]->getPosition().x << "," << mycirmodels[i]->getPosition().y << "\n";
*/
    myview.drawAll(mycirmodels);
  }
  return 0;
}
