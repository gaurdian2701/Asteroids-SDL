# Asteroids using a custom Entity-Component System

This is a project made using C++ 20, SDL3 and CMake.\
If you want to take a look at the ECS Code, go here:\
[ECS Code](https://github.com/gaurdian2701/SDL-Engine/tree/main)

## Game Implementation

The Game is currently finished with a full game loop.
My school assignment required me to use the Action Stack pattern in the game, so I've used it in the following scenarios:
- Scenes are loaded using an action stack approach. This means the scene on top of the stack can keep updating while the scene/s below it can be static with no updates.
- AI and player logic. I used reusable pieces of actions that became shared between the player and and AI. For example there was this "Move Action" that I created which ended up being used by both the player and the AI spaceship.

The game contains the following scenes:
- Main Menu
- Game Scene
- Game Over Scene


