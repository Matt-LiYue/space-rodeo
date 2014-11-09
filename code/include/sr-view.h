#include <SFML/Graphics.hpp>
#include "sr-control.h"
#include "sr-hud.h"


class View{
  public:
    View();
    void drawAll(std::vector<CircleModel*>&);
    void setController(Control&);
    bool isRun();
    void drawHUD(HUD&);
    void clear();
    void display();
  private:
    sf::RenderWindow _view;
    sf::Event _event;
    Control* _controller;
    sf::Texture _bgtexture;
    sf::Sprite _bgsprite;
};
