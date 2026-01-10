#pragma once
#include <managers/FontManager.hpp>
#include <app/GameContext.hpp>
#include <memory>

namespace Managers
{
	extern std::unique_ptr<FontManager> fontManagerPtr;
}

namespace Contexts
{
	extern std::unique_ptr<GameContext> gameContextPtr;
}