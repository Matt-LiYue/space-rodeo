#include <SFML/Graphics.hpp>
#include "sr-control.h"


class View{
  public:
    View();
    void drawAll(std::vector<CircleModel*>&, std::vector<sf::Sprite*>&);
    void setController(Control&);
    bool isRun();
  private:
    sf::RenderWindow _view;
    sf::Event _event;
    Control _controller;
    sf::Texture _bgtexture;
    sf::Sprite _bgsprite;
};
