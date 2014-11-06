#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sr-view.h"
#include "sr-models.h"
#include "sr-hud.h"
#include <iostream>


int main(int argc, char** argv){
  for (int i = 0 ; i < 1; i++){
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
	    myControl.setHUD(&(myModels.getHUD()));
      	myView.clear();
	  	myView.drawAll(myCirModels);

		std::cout << "main cow: " << myModels.getHUD().getcow() << std::endl;
	 	myView.drawHUD(myModels.getHUD());
      	myView.display();
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
