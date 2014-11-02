#ifndef _SR_WORMHOLE_H_
#define _SR_WORMHOLE_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"

class Wormhole : public CircleModel{
  public:
    Wormhole(sf::Vector2f,int);
    bool getOpen();
    void setOpen(bool);
  private:
    bool _open;
    sf::Texture _texture;
    sf::Texture* _textpointer;
};

#endif