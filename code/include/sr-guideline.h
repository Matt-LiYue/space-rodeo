#ifndef _H_SR_GUIDELINE_
#define _H_SR_GUIDELINE_

#include "SFML/Graphics.hpp"
#include "sr-utils.h"
#include <iostream>

class Guideline : public sf::VertexArray {
  public:
    Guideline();
    bool draw;
    float length;
    void setLine(sf::Vector2f start, sf::Vector2f dir);
    

  private:
    int _segments;
    float _length;
    
};




#endif