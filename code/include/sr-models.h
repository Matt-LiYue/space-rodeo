#ifndef _H_SR_MODELS_
#define _H_SR_MODELS_

#include "sr-circleModel.h"
#include "sr-wormhole.h"
#include "sr-ship.h"
#include "sr-cow.h"
#include "sr-spaceRanch.h"
#include "sr-orbitPlanet.h"
#include "sr-asteroid.h"
#include "sr-hud.h"
#include <iostream>

class Models{
  public:
    Models(int);
    std::vector<CircleModel*> getcirmodels();
		std::vector<Animation*> getAnimations();
    HUD getHUD();
  private:
    std::vector<CircleModel*> _circlemodels;
    HUD _hud;
    int totallevel;
    int currentlevel;
};




#endif