#ifndef _SR_HUD_H_
#define _SR_HUD_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"

class HUD{
  public:
    HUD();
    void initialize(int, sf::Vector2f, int, int, int);
    sf::CircleShape geticon();
    void settext(std::string);
    sf::Text gettext();
    void setlife(int);
    void setcow(int);
    void setburst(int);
    int getlife();
    int getcow();
    int getburst();
  private:
    sf::Font _font;
    sf::CircleShape _icon;
    sf::Text _text;
    sf::Texture _texture;
    sf::Texture* _textpointer;
    int _burst;
    int _cow;
    int _life;
};


#endif