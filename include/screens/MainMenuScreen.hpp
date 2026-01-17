#pragma once
#include "screens/BaseScreen.hpp"

class MainMenuScreen : public BaseScreen
{
	explicit MainMenuScreen(sf::RenderWindow& window) : BaseScreen(window) {}

	void handleInput(const sf::Event& event) override;
	void update() override;
	void draw() override;
};