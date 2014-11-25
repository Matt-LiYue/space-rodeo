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
  static void inisound();
  static void burst();
  static void collect();
  static void crash();
  static void complete();
  static void die();
  static void musicon();
  static void musicoff();
  
};



#endif
