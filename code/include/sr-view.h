#include <SFML/Graphics.hpp>
#include "sr-model.h"

class View{
  public:
    View();
    void drawAll(std::vector<CircleModel*>);
    bool isRun();
  private:
    sf::RenderWindow _view;
    sf::Event _event;
};
