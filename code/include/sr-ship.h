#ifndef _SR_SHIP_H_
#define _SR_SHIP_H_

#include <SFML/Graphics.hpp>
#include <cfloat> /* epsilon */
#include "sr-utils.h"
#include "sr-circleModel.h"
#include "sr-lasso.h"
#include "sr-planet.h"
#include <iostream>

class Ship : public CircleModel{
	
	/* Constructor and types */
  public:
    typedef enum {
      REST,
      FLY,
			GRAVITY,
      BURST,
      ORBIT } ShipState;
			
    Ship(sf::Vector2f, int, int);
		
		/* accessors */
    int getburst();
    ShipState getState();
    Planet* getOrbitPlanet();
		float getDir();
    float getAngularVelocity();
		Lasso* getLasso();
		sf::Vector2f getLassoDest();
		
		/* mutators */
    void setState(ShipState);
    void setSpd(sf::Vector2f);
    void setOrbit(Planet*);
    void setBaseAngVelocity(float);
		void setAngularVelocity(float);
    void updateOrientation();
    void adjustSpd(int);
		void brake();
    void decelerate();
		void shoot();
		
  private:
    ShipState _shipState;
    int _burst;
    float _angularVelocity;
		float _baseAngVelocity;
    Planet* _orbiting;
    sf::Texture _texture;
    sf::Texture* _textpointer;
		Lasso* _lasso;
		sf::Vector2f _lassoDest;
};

#endif