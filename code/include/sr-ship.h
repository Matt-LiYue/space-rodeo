#ifndef _SR_SHIP_H_
#define _SR_SHIP_H_

#include <SFML/Graphics.hpp>
#include <cfloat> /* epsilon */
#include "sr-circleModel.h"
#include "sr-lasso.h"
#include "sr-planet.h"
#include <iostream>
#include <assert.h>
#include "sr-utils.h"


class Ship : public CircleModel{
	
	/* Constructor and types */
public:
	typedef enum {
		REST,
		FLY,
		GRAVITY,
		ORBIT,
		BURST } ShipState;
		
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
		sf::Vector2f updatePosition(float deltaTime);
		void setRelPos(sf::Vector2f); // sets relative position to planet
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
		
		float _period;
		
		
	private:
		ShipState _shipState;
		float _angularVelocity;
		float _baseAngVelocity;
		int _burst;
		Planet* _orbiting;
		sf::Texture _texture;
		sf::Texture* _textpointer;
		Lasso* _lasso;
		sf::Vector2f _lassoDest;
		sf::Vector2f _relPos;
		
		//sf::Vector2f _getRelPos();     // gets position relative to planet
	};

#endif