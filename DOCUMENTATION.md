# Genesis documentation
This file contains fairly comprehensive documentation on Genesis components and how they work, as well as code examples that can help you better understand the material.

### Table of contents
1. [**Brief note**](#brief-note)
2. [**Game Loop**](#game-loop)
3. [**Physics Simulation**](#physics-simulation)
4. [**Rendering Components**](#rendering-components)
5. [**Event Handling**](#event-handling)

## Brief note
- The code follows Google's style almost entirely, except for a few things I changed, but they are not related to naming and are not visible to the end user.
- For all mathematical operations, my implementation of a two-dimensional vector Vector2 is used with overloaded parameters and certain basic functions.
- The library has several shortcuts, located in the static class `genesis::Shortcuts`, which are intended to simplify the rendering code. Since the physical simulation uses the classic Cartesian coordinate system and takes the coordinates of objects as their center, and SDL2 displays objects from the upper left corner and its Y axis is inverted, a module is needed to convert physical properties to `SDL_FRect`, which is what the shortcuts are. They include the `PhysicalPropertiesToRect`, `PositionAndSizeToRect` and `PositionAndTextureToRect` functions.
- In all its code, Genesis uses my implementation of shared pointer. This was done for the purpose of some optimization, because `std::shared_ptr<T>` is thread-safe, which reduces performance. My implementation, namely `genesis::SharedPointer<T>`, is not thread-safe, since SDL2 is single-threaded and there is simply no need for thread-safety, and is an extremely thin wrapper, working with which is exactly the same as with `std::shared_ptr<T>`. The only thing is that there is no direct initialization by the parameters of the created object, but this is bearable.

## Game Loop
## Physics Simulation
## Rendering Components
## Event handling
