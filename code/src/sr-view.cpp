#include <SFML/Graphics.hpp>
#include "sr-view.h"
#include <iostream>

View::View(){
  _bgtexture.loadFromFile("bg.jpeg");
  _bgsprite.setTexture(_bgtexture);
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  _view.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32),"Space Rodeo", sf::Style::Default, settings);
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


void View::drawAll(std::vector<CircleModel*>& mycirmodels, std::vector<sf::Drawable*>& drawables){
  _view.draw(_bgsprite);
  while (_view.pollEvent(_event)){//TODO: Use Control Class to handle the event
    switch (_event.type){
      case sf::Event::Closed:
      _view.close();
      break;
      case sf::Event::KeyPressed:
        _controller->handleEvent(_event);
        break;
        
      case sf::Event::KeyReleased:
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
  for (int i = 0; i < drawables.size(); i++) {
    sf::Drawable* d = drawables[i];
    if (dynamic_cast<Guideline*>(d) != 0 && ((Guideline*) d)->draw) {
      _view.draw(*d);
    }
  }
  
}

bool View::isRun(){
  if (_view.isOpen())
    return true;
  else
    return false;
}

int View::transitionscreen(int i, int totallevel, bool die, bool insufcow){
  sf::Event event;
  sf::CircleShape icon(30);
  sf::Texture texture;
  sf::Text text;
  sf::Text text2;
  sf::Font font;
  bool select = false;
  font.loadFromFile("arial.ttf");
  text.setFont(font);
  text2.setFont(font);
  texture.loadFromFile("rock.png");
  icon.setTexture(&texture);
  icon.setPosition(300,350);
  text.setPosition(400,350);
  text2.setPosition(350,150);
  text.setCharacterSize(45);
  View::transtate state;
  int result;
    //START SCREEN
  if (die){
    text2.setCharacterSize(50);
    text2.setString("  You die!  \nLevel failed");
    text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
    state = RETRY;
    text.setString("RETRY\n\nEXIT GAME");
  }
  else if (insufcow){
    text2.setCharacterSize(50);
    text2.setString("Capture all cows to finish the level!");
    text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
    state = RETRY;
    text.setString("RETRY\n\nEXIT GAME");
  }
  else{
    if (i == 0){

      text2.setCharacterSize(60);
      text2.setString("SPACE RODEO");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = START;
      text.setString("START GAME\n\nEXIT GAME");
    }
    else if (i == totallevel){
      text2.setCharacterSize(45);
      text2.setString("    Congratulations!\nYou complete this game!");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = RESTART;
      text.setString("MAIN SCEME\n\nEXIT GAME");
    }
    else {
      text2.setCharacterSize(50);
      text2.setString("You finished this level!");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
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
      icon.setPosition(300,450);
      result = totallevel;
    }
    else{
      icon.setPosition(300,350);
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
    _view.draw(text2);
    _view.draw(icon);
    _view.display();
  }
  return result;
}
