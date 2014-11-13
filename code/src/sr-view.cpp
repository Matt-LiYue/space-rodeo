  #include <SFML/Graphics.hpp>
  #include "sr-view.h"
  #include <iostream>

View::View(){
  _bgtexture.loadFromFile("bg.jpg");
  _bgsprite.setTexture(_bgtexture);
  _view.create(sf::VideoMode(800,600,32),"Space Rodeo");
}


void View::setController(Control& controller){
  _controller = &controller;
}

void View::drawHUD(HUD& hud){
  hud.update();
  _view.draw(hud.getcowicon());
  _view.draw(hud.getbursticon());
  _view.draw(hud.getlifeicon());
  _view.draw(hud.gettext());
}
void View::clear(){
  _view.clear(sf::Color::Black);
}
void View::display(){
  _view.display();
}


void View::drawAll(std::vector<CircleModel*>& mycirmodels){
  _view.draw(_bgsprite);
  while (_view.pollEvent(_event)){//TODO: Use Control Class to handle the event
    switch (_event.type){
      case sf::Event::Closed:
      _view.close();
      break;
      case sf::Event::KeyPressed:
      _controller->handleEvent(_event);
      break;
      default:
      break;

    }
  }
  for (int i = 0; i < mycirmodels.size(); i++) {
    if (mycirmodels[i]->draw) {
     if (mycirmodels[i]->hasAnimation) {
      _view.draw(*mycirmodels[i]->getAnimation());
    }
    else {
      _view.draw(*mycirmodels[i]);
    }
  }
}

}

bool View::isRun(){
  if (_view.isOpen())
    return true;
  else
    return false;
}

int View::transitionscreen(int i, int totallevel, bool die){
  sf::Event event;
  sf::CircleShape icon(30);
  sf::Texture texture;
  sf::Text text;
  sf::Font font;
  bool select = false;
  font.loadFromFile("arial.ttf");
  text.setFont(font);
  texture.loadFromFile("rock.png");
  icon.setTexture(&texture);
  icon.setPosition(300,300);
  text.setPosition(400,300);
  text.setCharacterSize(45);
  View::transtate state;
  int result;
    //START SCREEN
  if (die){
    state = RETRY;
    text.setString("RETRY\n\nEXIT GAME");
  }
  else{
    if (i == 0){
      state = START;
      text.setString("START GAME\n\nEXIT GAME");
    }
    else if (i == totallevel){
      state = RESTART;
      text.setString("RESTART GAME\n\nEXIT GAME");
    }
    else {
      state = NEXTLEVEL;
      text.setString("NEXT LEVEL\n\nEXIT GAME");}
    }
    while (_view.isOpen() && !select){
      while (_view.pollEvent(event)){
        switch (event.type){
         case sf::Event::Closed:
         _view.close();
         break;
         case sf::Event::KeyPressed:
         if (event.key.code == sf::Keyboard::Down){
          if (state == START || state == NEXTLEVEL || state == RESTART || state == RETRY){
            state = EXIT;
          }
        }
        if (event.key.code == sf::Keyboard::Up){
          std::cout <<"pressed";
          if (die && state == EXIT){
            state = RETRY;
          }
          if (!die && state == EXIT && i == 0){
            state = START;
          }
          if (!die && state == EXIT && i == totallevel){
            state = RESTART;
          }
          if (!die && state == EXIT && i!=0 && i!=totallevel){
            state = NEXTLEVEL;
          }
        }

        if (event.key.code == sf::Keyboard::Space){
          select = true;
        }
        break;
        default:
        break;
      }
    }
    if (state == EXIT){
      icon.setPosition(300,400);
      result = totallevel;
    }
    else{
      icon.setPosition(300,300);
    }
    if (state == START)
      result = 0;
    if (state == RESTART)
      result = -i;
    if (state == NEXTLEVEL)
      result = 0;
    if (state == RETRY)
      result = -1;

    _view.clear();
    _view.draw(text);
    _view.draw(icon);
    _view.display();
  }
  return result;
}
