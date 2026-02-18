#pragma once
#include "screens/BaseScreen.hpp"

class SettingsScreen : public BaseScreen
{
public:
	explicit SettingsScreen() : BaseScreen() {}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) const override;

	~SettingsScreen() = default;
private: 
	
};