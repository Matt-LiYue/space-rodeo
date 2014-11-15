#include <SFML/Graphics.hpp>
#include "sr-wormhole.h"
#include "sr-ship.h"
#include "sr-cow.h"
#include "sr-spaceRanch.h"
#include "sr-orbitPlanet.h"
#include "sr-asteroid.h"
#include "sr-hud.h"
#include "sr-sound.h"
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
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
    
  private:    
    /* data members */
    bool _levelfinished;
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
