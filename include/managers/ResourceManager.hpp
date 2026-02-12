#pragma once
#include "managers/FontManager.hpp"
#include "managers/ActionManager.hpp"

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
	extern std::unique_ptr<ActionManager> actionManagerPtr;
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

	template <typename ...Ts>
	void checkActions(Ts&&... yuke)
	{
		actionManagerPtr->checkActions(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	bool hasAction(Ts&&... yuke)
	{
		return actionManagerPtr->hasAction(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	void clearActions(Ts&&... yuke)
	{
		actionManagerPtr->clearActions(std::forward<Ts>(yuke)...);
	}
}