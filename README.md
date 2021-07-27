# Haterminator
[Haterminator](gator-game-jam-2021) is a 2D, top-down, arena-based shooter game that I created in 45 hours during the Summer 2021 [Gator Game Jam](https://www.gatorgamejam.org/) at the University of Florida.

This is what was submitted to the game jam, I did not alter or modify the source code post-submission in any way.

Releases may be downloaded [here](https://github.com/lukas-vaiciunas/haterminator/releases/).

## Game Jam Overview
The theme for the Game Jam was "Anti-racism, Diversity, and Inclusion".

## The Development Process
I decided to develop the game from the ground up, creating a game engine from scratch in C++ using the [Allegro 5](https://liballeg.org/) C++ multimedia library. To save time with map creation, I created a basic [level editor](level-editor), also using [Allegro 5](https://liballeg.org/). In order to better fit the theme of the game, I opted to create my own [sprites and animations](gator-game-jam-2021/img) (but not the tileset, which was created by [o_lobster](https://o-lobster.itch.io/)). All of these decisions certainly subtracted time from designing the gameplay itself, but I made sure that Haterminator contains the defining constituents of a game:

- Objectives
- Rules
- Conflict
- Game State

## The Game
Haterminator is a 2D, top-down, arena-based shooter. In order to win, you must face and defeat five waves of enemies of increasing magnitude. You only have one life.

In order to remain consistent with the game jam's theme, the enemies are designed as manifestations of hate, which is the source of the game's name--a combination of the words "hate" and "terminator" to form "Haterminator".

## The Engine
The game engine is custom-made, created in C++ using the [Allegro 5](https://liballeg.org/) C++ multimedia library.

Design patterns used:
- [Game Loop](https://gameprogrammingpatterns.com/game-loop.html)
- [Pool](https://gameprogrammingpatterns.com/object-pool.html)
- [Event Queue](https://gameprogrammingpatterns.com/event-queue.html)
- [Subclass Sandbox](https://gameprogrammingpatterns.com/update-method.html)
- [Singleton](https://gameprogrammingpatterns.com/singleton.html)
- [State](https://gameprogrammingpatterns.com/state.html)
- [Update Method](https://gameprogrammingpatterns.com/update-method.html)
