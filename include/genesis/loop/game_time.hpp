#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_TIME_AVERAGE_GAME_TIME_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_TIME_AVERAGE_GAME_TIME_HPP_

namespace genesis
{
class GameTime
{
public:
    GameTime();

    float Delta();
    bool IsActive() { return is_active_; }

    void Activate() { is_active_ = true; }
    void Deactivate() { is_active_ = false; }

private:
    bool is_active_ = true;
    unsigned long long last_time_;
};
}

#endif
