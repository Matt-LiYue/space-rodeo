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
	  myView.setController(myControl);
		
	  while (myView.isRun()){
	    _mainclock.restart();
	    myView.drawAll(myCirModels, sprites);
	    _interval = _mainclock.getElapsedTime();
	    myControl.update(_interval.asSeconds());
	    if (myControl.getlevelfinished() == true) break;
			
			for (int i=0; i < myCirModels.size(); i++) {
				CircleModel* model = myCirModels[i];
				if (dynamic_cast<Lasso*>(model) != 0) {
					((Lasso*) model)->advanceFrame();
				}
			}
	  }
  }
  return 0;
}
