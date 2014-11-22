#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sr-view.h"
#include "sr-models.h"
#include "sr-hud.h"
#include <iostream>
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

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
    std::vector<CircleModel*>* myCirModels = myModels.getcirmodels();
    std::vector<Animation*>* animations = myModels.getAnimations();
		std::vector<sf::Drawable*>* drawables = myModels.getDrawables();
    myControl.setmodels(*myCirModels);
    myView.setController(myControl);
    


    while (myView.isRun()){
      _mainclock.restart();
      myControl.setHUD(&(myModels.getHUD()));
      myView.clear();
      myView.drawAll(*myCirModels, *drawables);
      myView.drawHUD(myModels.getHUD());
      myView.display();
      _interval = _mainclock.getElapsedTime();
      
      if (myControl.getlevelfinished() == true) break;
      if (myControl.getdie() == 1){//used one life
        if (myControl.getcrash() == true){
          myView.drawcrash(*myCirModels, *drawables, myModels.getHUD());
          myControl.setcrash(false);
        }
        myControl.setdie(0);
        myModels.restart();
        myModels.getHUD().setburst(3);
        myModels.getHUD().setcow(0);
      }
      else if (myControl.getdie() == 2){//life used up
        if (myControl.getcrash() == true){
          myView.drawcrash(*myCirModels, *drawables, myModels.getHUD());
          myControl.setcrash(false);
        }
        die = true;
        break;
      }
      else
        myControl.update(_interval.asSeconds());

			/*
      for (int j=0; j < animations->size(); j++) {
        (*animations)[j]->advanceFrame();
      }
			*/

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
