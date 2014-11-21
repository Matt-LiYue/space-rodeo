#ifndef _SR_CONTROL_H_
#define _SR_CONTROL_H_

#include <SFML/Graphics.hpp>
#include "sr-wormhole.h"
#include "sr-ship.h"
#include "sr-cow.h"
#include "sr-spaceRanch.h"
#include "sr-orbitPlanet.h"
#include "sr-asteroid.h"
#include "sr-hud.h"
#include "sr-sound.h"
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

class Control{
  public:
    Control();
    void update(float);
    void setmodels(std::vector<CircleModel*>&);
    void remakemodels();
    void handleEvent(sf::Event);
    bool getlevelfinished();
    void setHUD(HUD*);
    int getdie();
    void setdie(int);
    void die();
    bool getcrash();
    void setcrash(bool);

    
  private:    
    /* data members */
    bool _levelfinished;
    bool _crash;
    std::vector<CircleModel*>* _cirmodels;
    Ship* _ship;
    std::vector<Planet*> _planets;
    std::vector<Cow*> _cows;
    std::vector<Wormhole*> _wormholes;
    std::vector<Asteroid*> _asteroids;
    std::vector<OrbitPlanet*> _orbitPlanets;
    SpaceRanch* _ranch;
    void _removeModel(CircleModel*);
    void _setAngularVelocities(Planet* planet);
    HUD * _hud;
    GameSound _gsound;
    int _die;
    
};
#endif
