#ifndef _SR_PLANET_H_
#define _SR_PLANET_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"


class Planet : public CircleModel{
  public:
    Planet(sf::Vector2f,int,int);
    Planet(sf::Vector2f,int,int,int);
    sf::CircleShape getGravityCircle();
    sf::Vector2f getVelocity();
		float getGravMag();
    //void besun();
		
  private:
    int _gravitybound;
		float _gravMag;
    sf::Texture _texture;
    sf::Texture* _textpointer;
  
};

#endif