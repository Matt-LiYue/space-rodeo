#ifndef _SR_HUD_H_
#define _SR_HUD_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"

class HUD{
  public:
    HUD();
    void initialize(int, sf::Vector2f, int, int, int);
    sf::CircleShape getcowicon();
    sf::CircleShape getbursticon();
    sf::CircleShape getlifeicon();
    void settext(std::string);
    sf::Text gettext();
    void setlife(int);
    void setcow(int);
    void setburst(int);
    int getlife();
    int getcow();
    int getburst();
    void update();
  private:
    sf::Font _font;
    sf::CircleShape _cowicon;
    sf::CircleShape _bursticon;
    sf::CircleShape _lifeicon;
    sf::Text _text;
    sf::Texture _cowtexture;
    sf::Texture _bursttexture;
    sf::Texture _lifetexture;
    int _burst;
    int _cow;
    int _life;
};


#endif