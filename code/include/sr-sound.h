//
//  sr-sound.h
//
//
//

#ifndef ____sr_sound__
#define ____sr_sound__

#include <SFML/Audio.hpp>
#include <iostream>

class GameSound {
public:
  GameSound();
  void burst();
  void collect();
  void crash();
  void complete();
  
private:
  sf::Sound _sound;
  sf::SoundBuffer _buffer;
  int _play;
};



#endif
