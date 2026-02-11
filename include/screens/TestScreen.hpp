#pragma once
#include "screens/BaseScreen.hpp"
#include "ui/Row.hpp"

class TestScreen : public BaseScreen
{
public:
	explicit TestScreen() : BaseScreen() {
		p_row.setPosition(300.0f, 300.0f);
	}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

	~TestScreen() = default;

private:
	Row p_row;
};