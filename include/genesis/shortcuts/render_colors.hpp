#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHORTCUTS_RENDER_COLORS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHORTCUTS_RENDER_COLORS_HPP_

#include "SDL.h"

namespace arkanoid
{
class RenderColors
{
public:
    constexpr static SDL_Color kWhiteColor = {255, 255, 255, 255};
    constexpr const static SDL_Color kBlackColor = {0, 0, 0, 255};
};
}

#endif
