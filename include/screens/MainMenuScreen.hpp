#pragma once
#include "screens/BaseScreen.hpp"

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
};