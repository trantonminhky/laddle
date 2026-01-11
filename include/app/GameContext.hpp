#pragma once
#include "managers/FontManager.hpp"

// ////////////////////////////////////
// GAME STATES
enum class GameState
{
	NONE,
	TEST
};

class GameContext
{
public:
	GameContext(FontManager& fontManager) : p_fontManager(fontManager) {}

	template <typename ...Ts>
	void loadFont(Ts&&... yuke)
	{
		p_fontManager.l	oad(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	const sf::Font& getFont(Ts&&... yuke)
	{
		return p_fontManager.get(std::forward<Ts>(yuke)...);
	}

private:
	GameState p_currentState = GameState::NONE;
	FontManager& p_fontManager;
};