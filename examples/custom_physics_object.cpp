// An example of a simple Genesis application that contains all the necessary components for existence,
// as well as a physics simulation in which there are 2 simple test objects that accelerate
// over time and repel each other when they collide

#include "SDL.h"
#include "genesis/rendering/window_references.hpp"
#include "genesis/memory/shared_pointer.hpp"
#include "genesis/loop/game_time.hpp"
#include "genesis/events/application_events.hpp"
#include "genesis/loop/game_loop.hpp"
#include "genesis/rendering/screen_cleaner.hpp"
#include "genesis/events/input.hpp"
#include "genesis/exiting/application_exiter.hpp"
#include "genesis/rendering/screen_applier.hpp"
#include "genesis/loop/objects/game_object.hpp"
#include "genesis/shortcuts/shortcuts.hpp"
#include "genesis/physics/physics_simulation.hpp"

class Example : public genesis::IGameObject
{
public:
    Example(genesis::PhysicalProperties properties, genesis::WindowReferences references)
        : IGameObject(properties), references_(references) { }

    virtual void Update(float delta) override
    {
        SDL_FRect rect = genesis::Shortcuts::PhysicalPropertiesToRect(Properties());
        SDL_SetRenderDrawColor(references_.Renderer(), 255, 255, 255, 255);
        SDL_RenderDrawRectF(references_.Renderer(), &rect);
    }

    virtual void HandleCollisionStart(IPhysicsObject *other) override
    {
        Properties().velocity.x *= -1;
    }

private:
    genesis::WindowReferences references_;
};

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Example", 0, 0, 1920, 1080, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    auto window_references = genesis::WindowReferences(window, renderer);

    auto game_time = genesis::SharedPointer<genesis::GameTime>(new genesis::GameTime());
    auto application_events = genesis::SharedPointer(new genesis::ApplicationEvents());
    auto game_loop = genesis::SharedPointer(new genesis::GameLoop(game_time, application_events));

    auto screen_cleaner = genesis::SharedPointer(new genesis::ScreenCleaner(window_references));
    auto input = genesis::SharedPointer(new genesis::Input(application_events));
    auto exiter = genesis::SharedPointer(new genesis::ApplicationExiter(input));
    auto physics_simulation = genesis::SharedPointer(new genesis::PhysicsSimulation());

    game_loop->Add(screen_cleaner); // SYSTEM COMPONENT: clearing all render that was before this line
    game_loop->Add(application_events); // SYSTEM COMPONENT: gets all events from SDL2
    game_loop->Add(input); // SYSTEM COMPONENT: reading input from OS
    game_loop->Add(exiter); // SYSTEM COMPONENT: exiting from loop by pressing 'Escape'
    game_loop->Add(physics_simulation); // SYSTEM COMPONENT: updates all physics before other logic

    // Adding custom physics objects to loop
// =====================================================================================================================
    auto example1 = genesis::SharedPointer(new Example(genesis::PhysicalProperties {{ 500, 500 }, { 50, 50 }, { 1, 1 }, { 10, 10} }, window_references));
    game_loop->Add(example1);
    physics_simulation->Add(example1);

    auto example2 = genesis::SharedPointer(new Example(genesis::PhysicalProperties {{ 1500, 100 }, { 50, 50 }, { -1, 1 }, { -10, 10} }, window_references));
    game_loop->Add(example2);
    physics_simulation->Add(example2);
// =====================================================================================================================

    auto screen_applier = genesis::SharedPointer(new genesis::ScreenApplier(window_references));
    game_loop->Add(screen_applier); // SYSTEM COMPONENT: applies all render that was before this line
    game_loop->Activate();

    SDL_DestroyWindow(window_references.Window());
    SDL_DestroyRenderer(window_references.Renderer());
    SDL_Quit();
}
