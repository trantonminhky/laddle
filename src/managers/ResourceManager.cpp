#include "managers/ResourceManager.hpp"

namespace ResourceManager
{
	GameState currentState = GameState::MAIN_MENU;
	std::unique_ptr<FontManager> fontManagerPtr;
	std::unique_ptr<ActionManager> actionManagerPtr;

	void init()
	{
		fontManagerPtr = std::make_unique<FontManager>();
		fontManagerPtr->init();

		actionManagerPtr = std::make_unique<ActionManager>();
	}
}