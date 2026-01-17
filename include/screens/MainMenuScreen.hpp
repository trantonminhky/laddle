#pragma once
#include "screens/BaseScreen.hpp"

#include "contexts/GameContext.hpp"

struct MainMenuOption
{
	const char* name;
	const GameState nextState;
};

class MainMenuScreen : public BaseScreen
{
public:
	explicit MainMenuScreen(sf::RenderWindow& window) : BaseScreen(window) {}

	void handleInput(const sf::Event& event) override;
	void update() override;
	void draw() override;

private:
	int p_selector = 0;
	static constexpr auto MAIN_MENU_MAX_OPTIONS = 5;
	static constexpr MainMenuOption p_options[MAIN_MENU_MAX_OPTIONS] = {
		{"START", GameState::NOT_IMPLEMENTED},
		{"ABOUT", GameState::ABOUT},
		{"OPTIONS", GameState::OPTIONS},
		{"EXIT", GameState::NONE},
		{"TEST", GameState::TEST}
	};
};