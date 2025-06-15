# Technologies

Project is created with the use of c++ programing language, SFML3 library for window management, audio management and program screen management, and fastnoiselite library for creating scrolling map tile grids. 

Project has been made on Windows 10 with 16:10 screen-ratio being the basis for resolutions.

Game is played with keyboard input only.

# Features

- Basic file i/o which allows for saving overall game progress(upgrades and unlocks) and default settings.
- Settings which make you able to change: resolution, screen mode(fullscreen, borderless, windowed) and sound and music volumes
- Persistent upgrade system between diferent sessions which allows for upgrading basic stats of all characters
- 2 addtional unlockable maps and 3 characters which are unlocked by beating the previous map or beating the session with a previous character
- Full sound coverage including looping music
- In game menu displaying current weapons and items
- Persistent hud dislaying current hp, xp, level and timer
- 10 different enemy sprites changed every minute
- Power-up items dropping from enemy mini-bosses
- Item and weapon systems which include leveling, changing stats and evolutions

# Gameplay notes

Game is fully based on the Vampire survivors indie game and is played only with the use of arrow keys.

Each session lasts 10 minutes or up until death.

Game includes the weapon evolution system from the original.

Every certain amount of time a mini-boss is spawned which upon death drops power-up items which include healing, hp, evolution chest, bomb which kills all the enemies and coins for use in the persistent upgrade shop

Map layouts are consistent between different sessions and are generated based on the player position.

Enemies which are a certain distance from the player get despawned, unless they are mini-bosses in which case they get teleported to the other side of the screen.

Exiting from the in game menu does not update the coin amount, it is updated upon player's death or victory.

# Demonstration

Demonstration of the project at: https://www.youtube.com/watch?v=4WL2gd17ylE
