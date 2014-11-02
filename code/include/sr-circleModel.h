#ifndef _SR_CIRCLEMODEL_H
#define _SR_CIRCLEMODEL_H

#include <SFML/Graphics.hpp>
#include <math.h> /* fabs */

#include "sr-animation.h"

class CircleModel : public sf::CircleShape {
  public:
    bool _movable;
		bool draw;
    bool intersects(sf::CircleShape *other);
    sf::Vector2f getSpd();
    void setSpd(sf::Vector2f);
		Animation* getAnimation();
		void setPosition(sf::Vector2f);
		bool hasAnimation;
		
  protected:
    sf::Vector2f _spd;
		Animation _animation;
};

#endif