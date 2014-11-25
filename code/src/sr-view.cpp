#include <SFML/Graphics.hpp>
#include "sr-view.h"
#include <iostream>

View::View(){
  _bgtexture.loadFromFile("./art/bg.jpeg");
  _bgsprite.setTexture(_bgtexture);
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  _maintexture.loadFromFile("./bg/frame_0.jpg");
  _mainsprite.setTexture(_maintexture);
  _mainsprite.scale(float(WINDOW_WIDTH)/600,float(WINDOW_HEIGHT)/365);
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
void View::drawcrash(std::vector<CircleModel*>& mycirmodels, std::vector<sf::Drawable*>& drawables,HUD& hud){
  sf::Texture texture;
  Ship * ship;
  sf::Clock explodclock;
  sf::Time interval;
  explodclock.restart();
  for (int i = 0; i < (mycirmodels).size(); i++) {
    if (dynamic_cast<Ship*>((mycirmodels)[i]) != 0)
      ship = (Ship*) (mycirmodels)[i];
  }
  sf::CircleShape explode(30);
  int frameno = 10;

  interval = explodclock.getElapsedTime();
  while (interval.asSeconds()<1){
    std::string frame;
    std::stringstream out;
    out << int(interval.asSeconds()*10)+1;
    frame = out.str();
    texture.loadFromFile("./explosion/"+frame+".png");
    explode.setTexture(&texture);
    explode.setPosition(ship->getPosition()-sf::Vector2f(ship->getRadius(),ship->getRadius()));
    _view.clear(sf::Color::Black);
    drawAll(mycirmodels,drawables);
    drawHUD(hud);
    _view.draw(explode);
    _view.display();
    interval = explodclock.getElapsedTime();
  }
  
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
    if (dynamic_cast<Guideline*>(d) != 0 && ((Guideline*) d)->showLine) {
      _view.draw(*d);
    }
    else if (dynamic_cast<Guideline*>(d) == 0) {
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
  font.loadFromFile("AstronBoyWonder.ttf");
  text.setFont(font);
  text2.setFont(font);
  texture.loadFromFile("art/goat_ship8.png");
  icon.setTexture(&texture);
  icon.setTextureRect(sf::IntRect(126,0,66,66));
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
      text.setString("START GAME\nCONTROLS\nCREDITS\nEXIT GAME");
    }
    else if (i == totallevel){
      text2.setCharacterSize(45);
      text2.setString("    Congratulations!\nYou complete this game!");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = RESTART;
      text.setString("MAIN SCREEN\n\nEXIT GAME");
    }
    else {
      text2.setCharacterSize(50);
      text2.setString("You finished this level!");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = NEXTLEVEL;
      text.setString("NEXT LEVEL\n\nEXIT GAME");
    }
  }
  sf::Clock spriteclock;
  sf::Time interval;
  spriteclock.restart();
  while (_view.isOpen() && !select){
    while (_view.pollEvent(event)){
      switch (event.type){
       case sf::Event::Closed:
       _view.close();
       break;
       case sf::Event::KeyPressed:
       if (event.key.code == sf::Keyboard::Down){
        if (state == NEXTLEVEL || state == RESTART || state == RETRY){
          state = EXIT;
        }
        else if(state == CREDIT){
          state = QUIT;
        }
        else if (state == START){
          state = GUIDE;
        }
        else if (state == GUIDE){
          state = CREDIT;
        }
      }
      if (event.key.code == sf::Keyboard::Up){
        std::cout <<"pressed";
        if (die && state == EXIT){
          state = RETRY;
        }
        else if (!die && state == EXIT && i == totallevel){
          state = RESTART;
        }
        else if (!die && state == EXIT && i!=0 && i!=totallevel){
          state = NEXTLEVEL;
        }
        else if (state == QUIT){
          state = CREDIT;
        }
        else if (state == CREDIT){
          state = GUIDE;
        }
        else if (state == GUIDE){
          state = START;
        }
      }

      if (event.key.code == sf::Keyboard::Space){
        if (state == GUIDE){
          text2.setCharacterSize(40);
          text2.setString("Aim: LEFT/RIGHT\n Rocket Burst: SPACE\nThrow Lasso:\n\tLEFT\n\tUP\n\tRIGHT\nGuide Line: SHIFT\nBrake: DOWN\nMusic On: M\n Music Off\n");

          text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 50);
          state = BACK;
          text.setString("BACK");
          text.setPosition(400, 580);}
          else if (state == CREDIT){
            text2.setCharacterSize(40);
            text2.setString("CREDITS\n Images: Planet:http://puffleville.wikia.com/wiki/File:Angry-Birds-Space-Red-Planet-Level-5-19-310x232.png \n Ranch: http://towns.gamepedia.com/File:Cow_farm.png\n Asteroid: http://imgarcade.com/1/asteroid-png/\n Wormhole: http://xolarix.deviantart.com/art/SpaceDock-373355292\nCrash: http://www.picgifs.com/graphics/bombs/ \nBackground: http://giphy.com/gifs/astronomy-meteor-astrophotography-bDvL2sCunIvYI\n");
            text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 50);
            state = BACK;
            text.setString("BACK");
            text.setPosition(400, 580);
          }
            else if (state == BACK){
              text2.setCharacterSize(60);
              text2.setString("SPACE RODEO");
              text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
              state = START;
              text.setString("START GAME\nCONTROLS\nCREDITS\nEXIT GAME");
              text.setPosition(400,350);
            }
              else{
                select = true;
              }
            }
            break;
            default:
            break;
          }
        }
        if (state == EXIT){
          icon.setPosition(300,450);
        }
        else if (state == QUIT) {
          icon.setPosition(300,500);
        }
        else if (state == CREDIT){
          icon.setPosition(300,450);
        }
        else if (state == GUIDE){
          icon.setPosition(300,400);
        }
        else if (state == BACK){
          icon.setPosition(300, 580);
        }
        else 
          icon.setPosition(300,350);//START RETRY RESTART

        if (state == START)
          result = 0;
        if (state == RESTART)
          result = -i;
        if (state == NEXTLEVEL)
          result = 0;
        if (state == RETRY)
          result = -1;
        if (state == EXIT || state == QUIT){
          result = totallevel;
        }
        std::string frame;
        std::stringstream out;
        interval = spriteclock.getElapsedTime();
    out << int((21*150+interval.asMilliseconds())/150) % 42; // start from frame 21
    frame = out.str();
    _maintexture.loadFromFile("./bg/frame_"+frame+".jpg");
    _mainsprite.setTexture(_maintexture);
    _view.clear();
    _view.draw(_mainsprite);
    _view.draw(text);
    _view.draw(text2);
    _view.draw(icon);
    _view.display();
  }
  return result;
}


