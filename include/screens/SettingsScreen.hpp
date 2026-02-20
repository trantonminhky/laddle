#pragma once
#include "screens/BaseScreen.hpp"

#include "ui/Spinner.hpp"

constexpr auto SPINNERS_COUNT = 2;

class SettingsScreen : public BaseScreen
{
public:
	explicit SettingsScreen();

	bool handleInput(const sf::Event &event) override;
	void update() override;
	void draw(sf::RenderTarget& window) const override;

	~SettingsScreen() = default;

private:
	int p_selector = 0;
	std::array<std::unique_ptr<Spinner>, SPINNERS_COUNT> p_spinners;

	void p_drawTexts(sf::RenderTarget& window, const sf::Font& font) const;
	void p_drawSelector(sf::RenderTarget& window, const sf::Font& font) const;
	void p_drawSpinners(sf::RenderTarget& window) const;
};