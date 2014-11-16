#ifndef _SR_SHIP_H_
#define _SR_SHIP_H_

#include <SFML/Graphics.hpp>
#include <cfloat> /* epsilon */
#include "sr-circleModel.h"
#include "sr-lasso.h"
#include "sr-guideline.h"
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
    Guideline* getGuideline();
    sf::Vector2f getLassoDest();
    float getLowSpd();
    float getBaseSpd();
    float getBoostSpd();
    
    
    /* mutators */
    sf::Vector2f updatePosition(float deltaTime);
    void setRelPos(sf::Vector2f); // sets relative position to planet
    void setState(ShipState);
    void setSpd(sf::Vector2f);
    void setOrbit(Planet*);
    //void setBaseAngVelocity(float); deprecated
    void setAngularVelocity(float);
    void updateOrientation();
    void adjustSpd(int);
    void brake(bool on);
    //void decelerate(); deprecated
    void shoot();
    void updateGuideline(bool on);
    
    //float _period;
    
    
  private:
    ShipState _shipState;
    float _angularVelocity;
    //float _baseAngVelocity; deprecated
    float _lowSpd;
    float _baseSpd;
    float _boostSpd;
    float _brakeMagnitude;
    int _burst;
    Planet* _orbiting;
    Lasso* _lasso;
    Guideline* _guideline;
    sf::Texture _texture;
    sf::Texture* _textpointer;
    sf::Vector2f _lassoDest;
    sf::Vector2f _relPos;
    sf::Vector2f _accel;
};

#endif