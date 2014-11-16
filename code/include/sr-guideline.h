#ifndef _H_SR_GUIDELINE_
#define _H_SR_GUIDELINE_

#include "SFML/Graphics.hpp"
#include "sr-utils.h"
#include "sr-planet.h"
#include "sr-wormhole.h"
#include "sr-cow.h"
#include "sr-asteroid.h"
#include <iostream>

class Guideline : public sf::VertexArray {
  public:
    Guideline();
    bool draw;
    float length;
    void setLine(sf::Vector2f start, sf::Vector2f dir);
    void applyEffects(std::vector<Planet*>, std::vector<Wormhole*>,
		                  std::vector<Asteroid*>, std::vector<Cow*>);

  private:
    int _segments;
		bool _gravityAim;
		float _fullLength;
    float _curLength;
		sf::VertexArray _fullLine;
    
};




#endif