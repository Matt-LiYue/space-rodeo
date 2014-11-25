//
//  sr-sound.cpp
//
//  Created by Kate Quinn
//
//

#include "sr-sound.h"
#include <SFML/Audio.hpp>

static sf::Music music;
static sf::SoundBuffer buffer1;
static sf::SoundBuffer buffer2;
static sf::SoundBuffer buffer3;
static sf::SoundBuffer buffer4;
static sf::SoundBuffer buffer5;
static sf::Sound collectsound;
static sf::Sound completesound;
static sf::Sound burstsound;
static sf::Sound oversound;
static sf::Sound collidesound;
static int _play;

GameSound::GameSound(){
  ;
}

void GameSound::inisound(){
  _play  = 1;
  buffer1.loadFromFile("./resources/collect.wav");
  buffer2.loadFromFile("./resources/complete.wav");
  buffer3.loadFromFile("./resources/burst.wav");
  buffer4.loadFromFile("./resources/die.wav");
  buffer5.loadFromFile("./resources/crash.wav");
  if(!music.openFromFile("./resources/song.wav")){
        std::cout <<"ERROR: song file did not load";
  }
  music.setLoop(true);
  music.setVolume(10);
  music.play();
  collectsound.setBuffer(buffer1);
  completesound.setBuffer(buffer2);
  burstsound.setBuffer(buffer3);
  oversound.setBuffer(buffer4);
  collidesound.setBuffer(buffer5);
}

void GameSound::burst(){
  burstsound.play();
}
void GameSound::collect(){
  collectsound.play();
}
void GameSound::crash(){
  collidesound.play();
}
void GameSound::complete(){
  completesound.play();
}
void GameSound::die(){
  oversound.play();
}
void GameSound::musicon(){
  music.play();
}
void GameSound::musicoff(){
  music.stop();
}
