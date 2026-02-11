#pragma once
#include "managers/FontManager.hpp"

// ////////////////////////////////////
// GAME STATES
enum class GameState
{
	NONE,
	MAIN_MENU,
	ABOUT,
	OPTIONS,
	TEST,
	NOT_IMPLEMENTED
};

namespace ResourceManager
{
	extern std::unique_ptr<FontManager> fontManagerPtr;
	void init();

	template <typename ...Ts>
	void loadFont(Ts&&... yuke)
	{
		fontManagerPtr->load(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	const sf::Font& getFont(Ts&&... yuke)
	{
		return fontManagerPtr->get(std::forward<Ts>(yuke)...);
	}
}