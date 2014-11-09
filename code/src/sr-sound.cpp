//
//  sr-sound.cpp
//
//  Created by Kate Quinn
//
//

#include "sr-sound.h"
#include <SFML/Audio.hpp>



GameSound::GameSound(){
  _play  = 1;
  
 }

void GameSound::burst(){
  if (!_buffer.loadFromFile("resources/burst.wav")){
    std::cout <<"ERROR: burst file did not load";
  }
  
  _sound.setBuffer(_buffer);
  _sound.play();
}

void GameSound::collect(){
  if (!_buffer.loadFromFile("resources/collect.wav")){
    std::cout <<"ERROR: burst file did not load";
  }
  
  _sound.setBuffer(_buffer);
  _sound.play();
}

void GameSound::crash(){
  if (!_buffer.loadFromFile("resources/crash.wav")){
    std::cout <<"ERROR: burst file did not load";
  }
  
  _sound.setBuffer(_buffer);
  _sound.play();

}

void GameSound::complete(){
  if (!_buffer.loadFromFile("resources/complete.wav")){
    std::cout <<"ERROR: burst file did not load";
  }
  
  _sound.setBuffer(_buffer);
  _sound.play();
  std::cout << "sound playing";}