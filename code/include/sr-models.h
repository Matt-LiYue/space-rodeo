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
    std::vector<CircleModel*>* getcirmodels();
    std::vector<Animation*>* getAnimations();
    std::vector<sf::Drawable*>* getDrawables();
    HUD& getHUD();
    void parse();
    void restart();
    int getcowno();
    void tokenizer(const std::string& str, std::vector<std::string>& tokens, std::string& delimiters);
  
  private:
    std::vector<CircleModel*> _circlemodels;
    std::vector<sf::Drawable*> _drawables;
    std::vector<Animation*> _animations;
    HUD _hud;
    int _totalcow;
    int _currentlevel;
};




#endif