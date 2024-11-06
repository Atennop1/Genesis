<div id="toc">
  <ul style="list-style: none">
    <summary>
      <h1> Genesis </h1>
    </summary>
  </ul>
</div>

![badge](https://img.shields.io/static/v1?label=Language&message=C%2b%2b&color=blue&style=for-the-badge)
![badge](https://img.shields.io/static/v1?label=Platform&message=Windows/Linux&color=red&style=for-the-badge)

## About project
Genesis is a simple game engine based on SDL2 and written in modern C++. The engine is used in my own project ArkanoidWithoutAnEngine, it appeared when I was doing that project and soon decided to separate the system part into a separate solution, like my first small engine. It's supported on both Windows and Linux, and can be connected as a static library or as a dynamic one. It is also written in a strictly OOP style, with minimal distortions.

### Structure
The structure of Genesis is quite straightforward and understandable. Everything revolves around the game loop, which simply updates all `IGameLoopObject` objects added to it and removes destroyed objects from itself until the application receives an event with the `GENESIS_EXIT_CODE` code, which is set as a custom code and has a value of `0x9999`. The physics simulation is also an `IGameLoopObject` and updates the `IPhysicsObjects` placed in it with a constant delta. There is an `IGameObject` cascade entity that combines `IGameLoopObject` and `IPhysicsObject` and is a full-fledged object that can be placed in the world, updated, or removed from it. More information about the structure of the engine and its built-in components can be found in the [**documentation**]().

### Techniques
- Clean OOP and DI
- Custom game loop
- Custom AABB physics simulation
- Self-written smart pointer

### Tools
- SDL2 
- CMake

## Conclusion 
The project became a big boost for me in understanding the work of game engines, the CMake build system and C++ in general. Thanks to it, I understood many things, faced many problems in development and overcame a long way from a simple vector ball output using the Windows API, to this, albeit small, but full-fledged engine, with its own physics, game cycle, memory management system, which can be assembled for both platforms and as a static and dynamic library. Also thanks to it, I understood how to develop and grow further, so now I am moving forward in a new direction, towards new challenges.
