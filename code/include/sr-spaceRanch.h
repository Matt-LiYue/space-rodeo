#ifndef _SR_SPACERANCH_
#define _SR_SPACERANCH_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"

class SpaceRanch : public CircleModel{
  public:
    SpaceRanch(sf::Vector2f, int);
  private:
    sf::Texture _texture;
    sf::Texture* _textpointer;
};

#endif