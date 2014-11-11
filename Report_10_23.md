####__Report on Oct 23, 2014__

* __Design Clarification__

The game is now a pure puzzle game. Each level is stand alone. Player tries to collect as many cows as possible and travel to the Space Ranch to finish one level, given limited resources. 

* __Work that has been done__
  * The game is based on MVC framework. Models store all the elements, view renders the elements, and Controller in charge of handling user input and self-movements of the objects. 
  * Player uses "left" and "right" key to adjust the firing direction of the spaceship, and press "enter" for firing.
  * Collision detection. The spaceship will crash if it runs into a planet, or flies out of bound.
  * Gravity force -- Spaceship orbiting the planet. An simple illustration is as follows:
  ![here](https://github.com/mstrotta/space-rodeo/blob/master/materials/gravity.png "Space Rodeo")
  * Part of the art and text file map input.
  ![here](https://github.com/mstrotta/space-rodeo/blob/master/code/art/cow.png "Cow")
  ![here](https://github.com/mstrotta/space-rodeo/blob/master/code/art/ranch.png "Space Ranch")
  ![here](https://github.com/mstrotta/space-rodeo/blob/master/code/art/rock.png "Rocket")
* __Core functionality remaining:__
  * Lasso: Spaceship shoots the lasso to capture cows
  * Trailing lasso to collect cows on planet
  * Enhancement:
    * Orbit smoothness and gravity "bend"
    * Stationary, moving obstacles
    * Worm holes
    * Art, music

* __Contribution:__
  Yue: Build the MVC framework, handle user input.
  Michael: Collision detection, gravity force.
  Kate: Art and text input.


