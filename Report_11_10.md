###__Report on Oct 23, 2014__

#### __Game Enhancement:__

* __Lasso is added:__ The spaceship now may shoot lasso to capture flying cows in the space. The lasso has its animation when shot out. The animation is implemented by showing different part sequently in the following figure.

![here](https://github.com/mstrotta/space-rodeo/blob/master/code/art/lasso.png "Lasso animation")

* __Sounds added:__ There are sounds added when the rocket launches, uses burst, and hit the obstacles.
* __Text input:__ The map information is now stored in text files instead of hardcoding in the program.
* __Changed orbiting mechanism:__ Previously, the rotation was implemented by using the rotate function. But it introduces troubles when doing collision detection. The rotation is now implemented using a vector-based mechanism. That is, we change the speed vector by changing its angles only. 
* __Space effects added:__ We have 2 more space effects implemented -- Asteroids and Wormholes. 

__Asteroids__ can move alone a direction in the game. Spaceship will be crashed when hit by an asteroid. Asteroids will crash when hit other objects, like space ranch, planets. Asteroids will appear at the origins after it crashes or goes out of the game bound.


![here](https://github.com/mstrotta/space-rodeo/blob/master/code/asteroid.png "Asteroids")

__Wormholes__ are places that transport the spaceship to another wormhole. Every wormhole has a counterpart. Entering either of the wormhole the spaceship will appear on the counterpart, keeping its velocity unchanged.


![here](https://github.com/mstrotta/space-rodeo/blob/master/code/wormhole.png "Wormholes")

* __Added indicators for cows, bursts, and life:__ Player will have limited bursts and life to finish one level. Player use bursts to escape planet gravity and avoid hit by asteroids. In order to finish each level, player will plan ahead how to best take advantage of the limited bursts to capture as many cows as possible. Player has limited life to retry the current level. 

![here](https://github.com/mstrotta/space-rodeo/blob/master/materials/HUD.png "Wormholes")
* __More levels are created__
* __The program is factored into separate files__
* __Added planet in motion__

#### __TODO:__
* Add more sounds and background music
* Add Transition between levels, game start and game over screens, etc
* Add bend effect of planets.
* More space effect, like blackhole, etc

#### __Contribution:__

  Yue: Space effects - asteroids and wormholes. Cow, life, and bursts indicators. burst deceleration.

  Michael: add and animate the lasso. Planet in motion. Vector-based orbiting implementation. 
  
  Kate: Art. Maps as text input. sound and music.