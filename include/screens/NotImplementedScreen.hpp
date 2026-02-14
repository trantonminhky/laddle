#pragma once
#include "screens/BaseScreen.hpp"

class NotImplementedScreen : public BaseScreen
{
public:
	explicit NotImplementedScreen() : BaseScreen() {}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

	~NotImplementedScreen() = default;

private:
	void p_drawText(sf::RenderTarget& window, const sf::Font& font);
};