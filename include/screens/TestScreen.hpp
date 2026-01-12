#pragma once
#include "screens/BaseScreen.hpp"
#include "ui/Row.hpp"

class TestScreen : public BaseScreen
{
public:
	explicit TestScreen(sf::RenderWindow& window) : BaseScreen(window) {
		p_row.setPosition(300.0f, 300.0f);
	}

	void handleInput(const sf::Event& event) override;
	void update() override;
	void draw() override;

	~TestScreen() = default;

private:
	Row p_row;
};