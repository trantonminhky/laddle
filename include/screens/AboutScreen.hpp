#pragma once
#include "screens/BaseScreen.hpp"

class AboutScreen : public BaseScreen
{
public:
	explicit AboutScreen() : BaseScreen() {}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) const override;

	~AboutScreen() = default;

private:
};