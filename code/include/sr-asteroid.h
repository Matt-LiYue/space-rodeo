#ifndef _SR_ASTEROID_H_
#define _SR_ASTEROID_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"

class Asteroid : public CircleModel{
  public:
    Asteroid(sf::Vector2f,int,sf::Vector2f);
    void replay();
    bool getExist();
    void setExist(bool);
  private:
    sf::Vector2f _oripos;
    sf::Texture _texture;
    sf::Texture * _textpointer;
    bool _exist;
};

#endif