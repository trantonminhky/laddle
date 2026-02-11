#pragma once
#include "screens/BaseScreen.hpp"

#include "contexts/GameContext.hpp"

class MainMenuScreen : public BaseScreen
{
public:
	explicit MainMenuScreen() : BaseScreen() {}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

private:
	int p_selector = 0;
	static constexpr auto MAIN_MENU_MAX_OPTIONS = 5;
	static constexpr GameState p_nextState[MAIN_MENU_MAX_OPTIONS] = {
		GameState::NOT_IMPLEMENTED,
		GameState::ABOUT,
		GameState::OPTIONS,
		GameState::NONE,
		GameState::TEST
	};
};