#pragma once
#include "screens/BaseScreen.hpp"

class NotImplementedScreen : public BaseScreen
{
public:
	explicit NotImplementedScreen() : BaseScreen() {}

	void handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

	~NotImplementedScreen() = default;
};