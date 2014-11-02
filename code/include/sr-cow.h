#ifndef _H_SR_COW_
#define _H_SR_COW_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"


class Cow : public CircleModel {
  public:
    Cow(sf::Vector2f,int);
		
  private:
    sf::Texture _texture;
    sf::Texture* _textpointer;
};

#endif