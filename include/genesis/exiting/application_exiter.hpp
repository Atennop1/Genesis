#ifndef GENESIS_INCLUDE_GENESIS_EXITING_APPLICATION_EXITER_HPP_
#define GENESIS_INCLUDE_GENESIS_EXITING_APPLICATION_EXITER_HPP_

#include "genesis/loop/objects/game_loop_object.hpp"
#include "genesis/memory/shared_pointer.hpp"
#include "genesis/events/input.hpp"

namespace genesis
{
class ApplicationExiter : public IGameLoopObject
{
public:
    ApplicationExiter(SharedPointer<Input> input);

    void Update(float delta) override;

private:
    Uint32 exit_event_type_;
    SharedPointer<Input> input_;
};
}

#endif
