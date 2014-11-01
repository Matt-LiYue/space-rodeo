#include <SFML/Graphics.hpp>
#include "sr-model.h"



class Control{
  public:
    Control();
    void update(float);
    void setmodels(std::vector<CircleModel*>&);
    void handleEvent(sf::Event);
    bool getlevelfinished();
		
  private:		
		/* data members */
    bool _levelfinished;
    std::vector<CircleModel*>* _cirmodels;
		Ship* _ship;
		std::vector<Planet*> _planets;
		std::vector<Cow*> _cows;
                std::vector<Wormhole*> _wormholes;
                std::vector<Asteroid*> _asteroids;
		SpaceRanch* _ranch;
		
		void _removeModel(CircleModel*);
		
};
