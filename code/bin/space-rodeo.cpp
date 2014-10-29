#include <SFML/Graphics.hpp>
#include <iostream>
#include "sr-view.h"
#include <unistd.h>

int main(int argc, char** argv){
  for (int i = 0 ; i < 2; i++){
	  Models myModels(i);
	  View myView;
	  Control myControl;
	  sf::Time _interval;
	  sf::Clock _mainclock;
	  std::vector<CircleModel*> myCirModels = myModels.getcirmodels();
	  myControl.setmodels(myCirModels);
		std::vector<sf::Sprite*> sprites = myModels.getSprites();
		std::cout << sprites.size() << std::endl;
	
	  myView.setController(myControl);
	  while (myView.isRun()){
	    _mainclock.restart();
	    myView.drawAll(myCirModels, sprites);
	    _interval = _mainclock.getElapsedTime();
	    myControl.update(_interval.asSeconds());
	    if (myControl.getlevelfinished() == true) break;
	  }
  }
  return 0;
}
