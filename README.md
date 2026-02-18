# Asteroids using a custom Entity-Component System

This is a project made using C++ 23, SDL3 and CMake.\
The following are links to my **ECS Code** .h and .cpp files in this repository:\
[ECS Headers](SDL-Engine/include/Core/ECS)\
[ECS Source Files](SDL-Engine/src/Core/ECS)\

If you want to take a look at the Components, [here is a link to them](SDL-Engine/include/Assets/Components).

The folders contain code for:
- An ECS Manager which handles creation, deletion and querying of components.
- Sparse Sets.
- Systems that use the ECS.
- A Component Factory. This simply creates component instances for each gameobject.

I currently have three systems implemented:
- A Rendering System that uses SDL for rendering textures on an SDL_Rect. It makes use of the Transform and Renderer2D Components.
- A Particle System that renders and simulates particles. I'd thought I could implement this since I had to program spaceships in my game anyway.
- A Transform Solver System. A simple system that solves transformations since I have parent-child transformations in the game. It is not very robust as I did not implement a hierarchy tree as I did not have the time, so all it does is blindly solve transforms for each object.

The game makes use of all three systems. Currently I am implementing game logic.
