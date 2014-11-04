#ifndef _SR_PLANET_H_
#define _SR_PLANET_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"


class Planet : public CircleModel{
  public:
    Planet(sf::Vector2f,int,int);
    sf::CircleShape getGravityCircle();
		sf::Vector2f getVelocity();
  private:
    int _gravitybound;
    sf::Texture _texture;
    sf::Texture* _textpointer;
  
};

#endif