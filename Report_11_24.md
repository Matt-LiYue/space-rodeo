###__Report on Oct 23, 2014__

* __Design Clarification__
The pure puzzle game has multiple stand-alone levels. Player has to collect all cows in a level to finish it. There are totally 6 levels with increasing difficulty. More space effects are presented  in the levels. 

* __New feature__
A real Billy: We now have a real Billy drawn by ourselves instead of using images from the Internet. Billy has 8 frames to show animations:
  ![here](https://github.com/mstrotta/space-rodeo/blob/master/code/art/goat_ship8.png "Billy")
Animation of Billy includes: Shoot a lasso, burst, brake

  Smooth orbit: Fixed the orbit gap. We are still using vector-based method to implement the orbiting while not having orbit gap.

  Planet Gravity: Spaceship will be pulled towards the orbiting planet slowly. So eventually the ship will crash on the planet if orbiting too long.
  
  Guidline: Used to provide more information such as gravity field of a planet and wormhole pairs. 
  
  Brake: decelerate
  
  Moving Planet: Planet can orbit a sun
  
  More animations:
crash, rope, lasso, background, burst, brake

  Transition screens
  More levels (6 in total)
  Music and more sound effects


* __Contribution:__
  Yue: Multi-dimensional lasso, crash animation, fix passing by values, background animation, transition screens, more levels

  Michael: Draw Billy, smooth orbit, guideline, brake, moving planet and planet gravity, rope animation, more levels
  
  Kate: Updated map editor, Music and sound effects, more levels, CREDIT and CONTROL instructions. 


