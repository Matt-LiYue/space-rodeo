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
    std::vector<CircleModel*> _cirmodels;
    bool _levelfinished;
};
