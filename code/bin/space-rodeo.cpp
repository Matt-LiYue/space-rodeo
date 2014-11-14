#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sr-view.h"
#include "sr-models.h"
#include "sr-hud.h"
#include <iostream>
int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 768;

int main(int argc, char** argv){
	View myView;
	sf::Time _interval;
	sf::Clock _mainclock;
	int totallevel = 4;
	bool die = false;
	bool insufcow = false;
	for (int i = 0 ; i < totallevel; i++){//i<=totallevel is just for displaying game finished screen
		if (i == 0 && myView.isRun()){// Start Screen
			i += myView.transitionscreen(i,totallevel,die,insufcow);
			if (i >= totallevel)
				exit(0);
		}
		Models myModels(i);
		Control myControl;
		std::vector<CircleModel*> myCirModels = myModels.getcirmodels();
		myControl.setmodels(myCirModels);
		std::vector<Animation*> animations = myModels.getAnimations();	
		myView.setController(myControl);
		//std::cout << "there are " << myCirModels.size() << " circle models\n";
		//std::cout << "there are " << animations.size() << " animations\n";
		while (myView.isRun()){
			_mainclock.restart();
			myControl.setHUD(&(myModels.getHUD()));
	    //std::cout << &(myModels.getHUD()) << std::endl; 
			myView.clear();
			myView.drawAll(myCirModels);
			myView.drawHUD(myModels.getHUD());
			myView.display();
			_interval = _mainclock.getElapsedTime();
			myControl.update(_interval.asSeconds());
			if (myControl.getlevelfinished() == true) break;
	    if (myControl.getdie() == 1){//used one life
	    	myControl.setdie(0);
	    	myModels.restart();
	    	myCirModels = myModels.getcirmodels(); //TODO: This is an ad-hoc solution, may need to update
	    	myControl.setmodels(myCirModels);
	    	animations = myModels.getAnimations();	
	    	myModels.getHUD().setburst(3);
	    	myModels.getHUD().setcow(0);
	    }
	    else if (myControl.getdie() == 2){//life used up
	    	die = true;
	    	break;
	    }

	    for (int j=0; j < animations.size(); j++) {
	    	animations[j]->advanceFrame();
	    }

	}
	if (myView.isRun()){
		if (myModels.getcowno() != myModels.getHUD().getcow())
			insufcow = true;
		i+= myView.transitionscreen(i+1,totallevel,die,insufcow);
		die = false;
		insufcow = false;
	}
	if (i>= totallevel)
		exit(0);
}
return 0;
}
