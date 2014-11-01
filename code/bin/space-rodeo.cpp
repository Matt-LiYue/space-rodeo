#include <SFML/Graphics.hpp>
#include <iostream>
#include "sr-view.h"
#include <unistd.h>

int main(int argc, char** argv){
  for (int i = 1 ; i < 2; i++){
	  Models myModels(i);
	  View myView;
	  Control myControl;
	  sf::Time _interval;
	  sf::Clock _mainclock;
	  std::vector<CircleModel*> myCirModels = myModels.getcirmodels();
	  myControl.setmodels(myCirModels);
		std::vector<Animation*> animations = myModels.getAnimations();	
	  myView.setController(myControl);
		
		std::cout << "there are " << myCirModels.size() << " circle models\n";
		std::cout << "there are " << animations.size() << " animations\n";
		
		
	  while (myView.isRun()){
	    _mainclock.restart();
	    myView.drawAll(myCirModels);
			
	    _interval = _mainclock.getElapsedTime();
	    myControl.update(_interval.asSeconds());
	    if (myControl.getlevelfinished() == true) break;

			for (int i=0; i < animations.size(); i++) {
					animations[i]->advanceFrame();
			}
			
	  }
  }
  return 0;
}
