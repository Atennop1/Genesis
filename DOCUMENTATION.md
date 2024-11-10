# Genesis documentation
This file contains fairly comprehensive documentation on Genesis components and how they work, as well as code examples that can help you better understand the material. You can also look at [**this file**](https://github.com/Atennop1/Genesis/blob/master/examples/README.md) if you need more complete examples.

### Table of contents
0. [**Notes**](#notes)
1. [**Game Loop**](#game-loop)
2. [**Physics Simulation**](#physics-simulation)
3. [**Rendering**](#rendering)
4. [**Event Handling**](#event-handling)

## Notes
- The code follows Google's style almost entirely, except for a few things I changed, but they are not related to naming and are not visible to the end user.
- For all mathematical operations, my implementation of a two-dimensional vector `genesis::Vector2` is used with overloaded parameters and certain basic functions.
- The library has several shortcuts, located in the static class `genesis::Shortcuts`, which are intended to simplify the rendering code. Since the physical simulation uses the classic Cartesian coordinate system and takes the coordinates of objects as their center, and SDL2 displays objects from the upper left corner and its Y axis is inverted, a module is needed to convert physical properties to `SDL_FRect`, which is what the shortcuts are. They include the `PhysicalPropertiesToRect`, `PositionAndSizeToRect` and `PositionAndTextureToRect` functions.
- In all its code, Genesis uses my implementation of shared pointer. This was done for the purpose of some optimization, because `std::shared_ptr<T>` is thread-safe, which reduces performance. My implementation, namely `genesis::SharedPointer<T>`, is not thread-safe, since SDL2 is single-threaded and there is simply no need for thread-safety, and is an extremely thin wrapper, working with which is exactly the same as with `std::shared_ptr<T>`. The only thing is that there is no direct initialization by the parameters of the created object, but this is bearable.

## Game Loop
The main object in the entire engine is, of course, the game loop. In Genesis, the `genesis::GameLoop` is designed in a very standard way: the `genesis::GameLoop` runs while `genesis::GameTime` is active (which can be deactivated if you need to), removes destroyed objects from the vector at the beginning of each frame, runs all `Update` method of all objects and stops running if SDL detects an event with the `GENESIS_EXIT_CODE` code, which is `0x9999` by default. After `genesis::GameLoop` is created, it needs to be activated. The `genesis::ApplicationExiter` component is provided out of the box, which sends such an event when the Escape key is pressed. But if you need to emit an event in other cases, you can simply create a custom event and assign it the `GENESIS_EXIT_CODE` code.

Know that `genesis::IGameLoopObject` is an object that can be added to the `genesis::GameLoop` and which can be updated and destroyed. Together with `genesis::IPhysicsObject` (which we'll talk about later), they form the `genesis::IGameObject` facade.

An example of code that creates a `genesis::GameLoop` and adds `genesis::ApplicationEvents` to it (which we'll talk about later):

```cpp
auto game_time = genesis::SharedPointer<genesis::GameTime>(new genesis::GameTime());
auto application_events = genesis::SharedPointer(new genesis::ApplicationEvents());

auto game_loop = genesis::SharedPointer(new genesis::GameLoop(game_time, application_events));
game_loop->Add(application_events);
game_loop->Activate();
```

## Physics Simulation
The physics simulation in Genesis is quite simple and is built on the AABB principle. The `genesis::PhysicsSimulation` object itself is a `genesis::IGameLoopObject` and updates the objects in the physics simulation in its `Update` method with a fixed delta. It also removes destroyed objects at the beginning of an iteration, looks for collisions between objects using a simple mathematical formula, and then handles each collision by calling the `HandleCollisionStart` method on both objects and passing them references to each other. Unfortunately, there is no collision solving here, nor are there any other methods for handling collisions (e.g. `HandleCollisionEnd`).

Note that the simulation objects have a `genesis::IPhysicsObject` interface, which allows them to be updated, know about collisions, be destroyed, and contain physics information (position, size, velocity, and acceleration). In Genesis, all simulation objects are rectangles in a Cartesian coordinate system with coordinates at the center.

An example of code that creates a simulation, adds 2 custom physics objects to it, and then adds the simulation itself to `genesis::GameLoop`:
```cpp
class Example : public genesis::IGameObject
{
public:
    Example(genesis::PhysicalProperties properties)
        : IGameObject(properties) { }
        
    virtual void HandleCollisionStart(IPhysicsObject *other) override
    {
        Properties().velocity.x *= -1;
    }
};

auto game_time = genesis::SharedPointer<genesis::GameTime>(new genesis::GameTime());
auto application_events = genesis::SharedPointer(new genesis::ApplicationEvents());
auto game_loop = genesis::SharedPointer(new genesis::GameLoop(game_time, application_events));
auto physics_simulation = genesis::SharedPointer(new genesis::PhysicsSimulation());

auto example1 = genesis::SharedPointer(new Example(genesis::PhysicalProperties {{ 500, 500 }, { 50, 50 }, { 1, 1 }, { 10, 10 } }, window_references));
auto example2 = genesis::SharedPointer(new Example(genesis::PhysicalProperties {{ 1500, 100 }, { 50, 50 }, { -1, 1 }, { -10, 10 } }, window_references));
physics_simulation->Add(example1);
physics_simulation->Add(example2);

game_loop->Add(application_events); 
game_loop->Add(physics_simulation);
game_loop->Add(example1);
game_loop->Add(example2);

game_loop->Activate();
```

## Rendering
Rendering in Genesis is entirely done by SDL2, except that shortcuts are provided to simplify the rendering code (described in the Notes) and some objects are out of the box. There is a DTO `genesis::WindowReferences`, which contains pointers to `SDL_Renderer` and `SDL_Window`, so that all the information about the window can be stored in one object. There are also objects `genesis::ScreenCleaner` and `genesis::ScreenApplier`, which clear the screen and display changes to it, respectively. These objects should be placed at the beginning and end of `genesis::GameLoop`, and all the rendering of the game should happen between them.

Code with examples, in which these objects and another test object are created:
```cpp
class Example : public genesis::IGameObject
{
public:
    Example(genesis::PhysicalProperties properties, genesis::WindowReferences references)
        : IGameObject(properties), references_(references) { }

    virtual void Update(float delta) override
    {
        SDL_FRect rect = genesis::Shortcuts::PhysicalPropertiesToRect(references_.Window(), Properties());
        SDL_SetRenderDrawColor(references_.Renderer(), 255, 255, 255, 255);
        SDL_RenderDrawRectF(references_.Renderer(), &rect);
    }

private:
    genesis::WindowReferences references_;
};

// creating SDL2 window...
auto window_references = genesis::WindowReferences(window, renderer);

auto game_time = genesis::SharedPointer<genesis::GameTime>(new genesis::GameTime());
auto application_events = genesis::SharedPointer(new genesis::ApplicationEvents());
auto game_loop = genesis::SharedPointer(new genesis::GameLoop(game_time, application_events));
    
auto screen_cleaner = genesis::SharedPointer(new genesis::ScreenCleaner(window_references));
auto screen_applier = genesis::SharedPointer(new genesis::ScreenApplier(window_references));
auto example = genesis::SharedPointer(new Example(genesis::PhysicalProperties {{ 500, 500 }, { 50, 50 }, { 1, 1 }, { 10, 10 } }, window_references));

game_loop->Add(application_events); 
game_loop->Add(screen_cleaner); 
game_loop->Add(example);
game_loop->Add(screen_applier);

game_loop->Activate();
```

## Event Handling
For events in Genesis, events from SDL2 and 2 components are used, namely `genesis::ApplicationEvents` and `genesis::Input`. `genesis::ApplicationEvents` receives events from SDL2 every frame and sorts them by types and codes, and then they can be read by other components such as `genesis::GameLoop`. `genesis::Input` is an add-on to `genesis::ApplicationEvents`, from which you can find out whether a certain key is currently pressed or which ones were pressed in the current frame.

An example of code using event handling, in which an object moves when you press the arrow keys on the keyboard:
```cpp
class Example : public genesis::IGameObject
{
public:
    Example(genesis::PhysicalProperties properties, genesis::WindowReferences references, genesis::SharedPointer<genesis::Input> input)
        : IGameObject(properties), references_(references), input_(input) { }

    virtual void Update(float delta) override
    {
        if (input_->IsKeyPressed(SDLK_LEFT) ^ input_->IsKeyPressed(SDLK_RIGHT))
            Properties().position += genesis::Vector2(40 * (input_->IsKeyPressed(SDLK_LEFT) ? -1.0f : 1.0f) * delta, 0.0f);

        SDL_FRect rect = genesis::Shortcuts::PhysicalPropertiesToRect(references_.Window(), Properties());
        SDL_SetRenderDrawColor(references_.Renderer(), 255, 255, 255, 255);
        SDL_RenderDrawRectF(references_.Renderer(), &rect);
    }

private:
    genesis::WindowReferences references_;
    genesis::SharedPointer<genesis::Input> input_;
};

// creating SDL2 window...
auto window_references = genesis::WindowReferences(window, renderer);

auto game_time = genesis::SharedPointer<genesis::GameTime>(new genesis::GameTime());
auto application_events = genesis::SharedPointer(new genesis::ApplicationEvents());
auto game_loop = genesis::SharedPointer(new genesis::GameLoop(game_time, application_events));

auto input = genesis::SharedPointer(new genesis::Input(application_events));
auto screen_cleaner = genesis::SharedPointer(new genesis::ScreenCleaner(window_references));
auto screen_applier = genesis::SharedPointer(new genesis::ScreenApplier(window_references));
auto example = genesis::SharedPointer(new Example(genesis::PhysicalProperties {{ 500, 500 }, { 50, 50 } }, window_references, input));

game_loop->Add(screen_cleaner); 
game_loop->Add(application_events); 
game_loop->Add(input); 
game_loop->Add(example);
game_loop->Add(screen_applier);

game_loop->Activate();
```
