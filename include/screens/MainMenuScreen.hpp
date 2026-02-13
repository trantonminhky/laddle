#pragma once
#include "screens/BaseScreen.hpp"

#include "managers/ResourceManager.hpp"

class MainMenuScreen : public BaseScreen
{
public:
	explicit MainMenuScreen() : BaseScreen() {}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

private:
	int p_selector = 0;
	static constexpr auto P_MAIN_MENU_MAX_OPTIONS = 5;
	static constexpr GameState p_nextState[P_MAIN_MENU_MAX_OPTIONS] = {
		GameState::PLAY,
		GameState::ABOUT,
		GameState::OPTIONS,
		GameState::NONE,
		GameState::TEST
	};
};