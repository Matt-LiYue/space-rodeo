__pace Rodeo - Design Document__ 

----------
### __1. Title page__

----------

![here](https://github.com/mstrotta/space-rodeo/blob/master/materials/Screen%20Shot%202014-10-13%20at%2012.26.41%20PM.png "Space Rodeo")

### __2. Executive summary__


----------


Earth’s cows have been abducted into space by an Extraterrestrial Evil Cow Overlord and, if nothing is done to stop him, will be used as part of his Mad Cow army. The courageous cowgoat Billy the Kid ventures from his Wild West home into space to round up the lost cows and defeat the evil cow overlord. Along the way he must master and make use of the physics of the Milky Way.

### __3. Overview__


----------


   * Title: Space Rodeo
   * Tagline: “Would you like fries with that milkshake?”
   * Team Members: Yue Li, Michael Trotta, Kate Quinn, Joe Soultanis
   * Genre: Physics Puzzles
   * Platform: PC
   * Market: Ages 7 to 50
   * Setting: Space
   * Plays like: Angry Birds meets Run from the Sun with a Western theme

### __4. Related Games__


----------


####__Angry Birds__
* __Developer:__ Rovio Entertainment
* __Platform:__ Apple iOS
* __Year:__ 2009
* The game has been called “the largest mobile app success the world has seen,” and the mobile app has inspired an entire franchise of related work, including a television series and an Angry Birds Space-themed park at Kennedy and Houston NASA Space Centers. Look for a Sony Pictures Entertainment animated film in 2016.

#### __Cows in Space__

 * __Developer:__ Donut Games
 * __Platform:__ Apple iOS
 * __Year:__ 2014
 * Similar to Space Rodeo in theme: cows are floating around in space and must be teleported back to Earth. The gameplay is a puzzle game where the player shoots projectiles from a left-right moving shooter to try to knock cows into stars in a Peggle/Pong-type game. There are some interesting gravity mechanics that we may use for inspiration.

####__Run from the Sun__
* Publisher: Armor Games
* Platform: PC
* Year: 2011
* Player controls a space ship, which they launch from one planet to another in a side-scrolling journey, racking up points for distance and other achievements. Players must time the firing of a rocket pulse with the rotation of a planet in order to succeed. Ship upgrades are given for points.

###__5. Player composition__


----------


__General__
Space Rodeo is targeted to casual gamers between age 7 and 50 who enjoy addictive puzzles such as Angry Birds. Players play the game during down-time at work or at school on their PC's. Play time is therefore limited to about 10 minutes per session, 3-5 times per week until completing the game. The difficulty of each level must be such that each level can be beaten by the average player in less than 10 minutes. The goal is to keep the player excited to return to the game when they have another block of free time, so each successive level must contain a new or interesting challenge that has not been seen before.
    
Players likely find out about the game through social media or through gaming websites such as addictingGames.com. The game is free to play.

Addicting gameplay and the desire to overcome the puzzle of each level is the primary driver for gameplay, but the inclusion of a playful cartoon theme will serve to give personality to the game and may become the foundation of a franchise much the way Angry Birds has become a franchise.

__Player profiles:__
    
Brian, a 42 year-old male, catches his obviously frustrated coworker playing Space Rodeo before their meeting gets started at the office. He is more than a little intrigued by his coworker's explanation: “I didn't have enough rocket boosts to capture the 9th cow.” Brian has a history of playing Facebook games, and he determines to look into the new game when he gets some free time.

Owen, a 8 year-old male student, has discovered a passion for online flash games in the computer lab during his after-school program. He comes across Space Rodeo and begins playing it side-by-side a few friends consistently after school for a week and a half until he has beaten the game.

Jessica is an 18 year-old college student who would rather do anything on her open laptop but take notes from her Psychology professor's lecture.  She has consequently endeavored to beat as many levels as possible from Space Rodeo, which her like-minded classmate has just linked her, as the 80 minute lecture period affords.

### __6. World__


----------
The game takes place in our own Milky Way galaxy. However, Billy the Kid must venture farther and farther from his home planet, Earth, and its surrounding solar system in his relentless pursuit of Earth's cows. In his world, many animals are anthropomorphized to speak English and engage in human-like activities such as playing checkers and rounding up cattle. Others, such as the Evil Cow Overlord, come from distant galaxies and thus have unnatural abilities and technologies and inexplicably evil intentions. However, some animals retain their natural animalistic natures, such as the cows which are the object of Billy the Kid's round-ups.

There also exist far more unique space effects such as black holes, worm holes, and asteroids than the scientists of our own Earth believe exist

### __7. Characters__


----------


Billy the Kid draws quicker, spits farther, and shoots straighter than any other goat in Texas. He's a true Western cowboy and has proved a mighty fine sheriff of his town, where he's rounded up villain and bovine like for the past few years. You'll find him walking on hind-legs, lasso on his hip, characteristic red neckerchief about his neck, well-polished sheriff star on his breast, and hat sitting neatly around his polished horns. This white goat with brown patches has earned a name for himself in the West, but he'll have to prove he can hold his own across the entire Milky Way in short time, since all of Earth's cows have been mysteriously abducted. Billy has no interest in his species becoming Earth's de facto dairy producer, so he must take Huston's newly minted space ship and try to recover them.

The Evil Cow Overlord is a mysterious bovine extraterrestrial who has appeared in the Milky Way Galaxy uninvited and intends to use Earth's cows for nefarious purposes. He is a characteristically large dairy cow with intimidating horns, mad red eyes, and the propensity to shoot milk at any enemy that he may engage with. His plan is to turn Earth's cows into his own Mad Cow minions through some sort of mind control.

###__8. Progression graph__


----------


###__9. Art direction__


----------


###__10.UI story boards__


----------


###__11.Tags & Dialog__


----------

__TAGS:__

__SHOOT__ = "Shoot lasers"

__WITHDRAW__ = "Withdraw lasers"

__LASSO__ = "Go lasso"

__CUT__ = "Cut lasso"

__MOVE__ = "Move the ship"

__Dialog examples:__

"You haven't seen the last of us!"

"MOOOOOOOO"

"Another day, another lasso"

###__12.Technology plan__


----------


###__13.Software architecture__


----------
![here](https://github.com/mstrotta/space-rodeo/blob/master/materials/UML%20Design.jpg "Space Rodeo")

###__14.Controls__
We control the spaceship of Billy traveling in the space. The control mechanism is much like Angry Birds. Player almost loses control of track of the space after firing it with one exception -- bursts that can escape the gravity of a planet. Player has the ability to shoot lassos when flying or trailing lassos when orbiting a planet to collect cows. Player needs to plan ahead to make good use of limited bursts to collect as many as cows and eventually fly to the destination of each level. There are 4 kinds of control.

* __Launching:__ In each level, there is a starting point at which the spaceship can be shot into the space. Player presses "left" and "right" arrows to change the direction. Afterward player press "enter" to launch the spaceship.
* __Burst:__ Player has limited burst in each level. The burst number depends on the spaceship Billy owns. When using a burst (press "space") , the spaceship can temporarily escape the space effect (escape orbiting a planet or escape black holes). 
* __Shoot Lasso:__ When spaceship is flying, player can press "up" or "down" to shoot a lasso in corresponding direction to capture flying mad cows. 
* __Trailing Lasso:__ When spaceship is orbiting a planet, player can press "enter" to start trailing lasso. After circling a planet, all walking cows in the planet will be captured.

----------


###__15.Level design__

----------

Space Rodeo has multiple levels. To reach the next level, player has to collect sufficient number (level-dependent) of cows in the current level, as well as reach the destination -- Space Ranch --  of the current level. In each level, player will deal with new space effect. An illustration is shown below
![here](https://github.com/mstrotta/space-rodeo/blob/master/materials/SpaceRodeo_illustration.jpg "Space Rodeo")
The lower part of this figure shows the most basic level, player simply fires the spaceship in the direction of Space Ranch. Then the level is finished. The higher part of this figure shows a more advanced level. In order to finish this level, player needs to deliberate how to capture the flying mad cow and reaches the Space Ranch while not crashing on the obstacles. In this level, player can take advantage of the gravity of the planet to change its track. 


###__16.Mechanics analysis__


----------
* __Map Objectives:__ Player must capture a certain quota of cows on each level and reach the Space Ranch on the map. He lassos cows by either encircling cows on planets while orbiting the planets or by shooting a lasso rope in one direction
* __Survival:__ Player has finite number of lives which are lost upon crashes into objects and the map edges
* __Movement:__ Player controls his space ship’s movement by rotating his ship and by firing a rocket. He may 
* __Gravity:__ Planet in the map has gravity impact on the spaceship, which will lead to crash, orbit, or curve depending on the track of the spaceship.
* __Space Effects:__ Player must engage with various space effects such as worm holes (map teleportation effect) and deadly asteroids.
* __Burst:__ Player has limited number of bursts to alter the track of spaceship in order to collect more cows or avoid dangers. 
* __Cow usage:__ Player aims to collect more mad cow for currency, which can be used in Space Shop.
* __Space Shop:__ Player can purchase advanced spaceship, spaceship parts and even life in Space Shop. Space Shop locates at certain levels, which can be visited by traveling through it.


###__17.Schedule__

> Oct 17 -- Game prototype and skeleton

> Oct 22 -- Basic sprites

> Oct 22 -- Milestone: game playable and tolerable visuals

> Oct 23 -- Progress presentation

> Oct 31 -- Shop System

> Nov 7 --  Enrich elements and levels 

> Nov 10 -- Sounds and music

> Nov 10 -- Milestone: Game roughly look like the final version

> Nov 11 -- Progress presentation

> Nov 21 -- Improve sprites, elements and levels

> Nov 23 -- Testing and Refining

> Nov 24 -- Final presentation and demo

> Nov 28 -- Final refinement

> Nov 28 -- Milestone: Game complete

> Dec 4 -- Final report 

###__18.Budget__
4 People, 3 Months
###__19.Changelog__
The github repository serves as the changelog of our project.



