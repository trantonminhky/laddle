#include <iostream>

#include "screens/MainMenuScreen.hpp"

#include "helper/centerTextInRect.hpp"

#include "managers/ScreenManager.hpp"

constexpr auto LADDLE_TEXT_Y_POSITION = 100.0f;
constexpr auto PLAY_TEXT_Y_POSITION = 300.0f;
constexpr auto ABOUT_TEXT_Y_POSITION = 380.0f;
constexpr auto SETTINGS_TEXT_Y_POSITION = 460.0f;
constexpr auto EXIT_TEXT_Y_POSITION = 540.0f;
constexpr auto TEST_TEXT_Y_POSITION = 620.0f;

bool MainMenuScreen::handleInput(const sf::Event& event)
{
	if (event.is<sf::Event::KeyPressed>())
	{
		auto scancode = event.getIf<sf::Event::KeyPressed>()->scancode;
		if (scancode == sf::Keyboard::Scan::Up || scancode == sf::Keyboard::Scan::W)
		{
			p_selector = (p_selector + MAIN_MENU_MAX_OPTIONS - 1) % MAIN_MENU_MAX_OPTIONS;
		}
		else if (scancode == sf::Keyboard::Scan::Down || scancode == sf::Keyboard::Scan::S)
		{
			p_selector = (p_selector + 1) % MAIN_MENU_MAX_OPTIONS;
		}
		else if (scancode == sf::Keyboard::Scan::Enter)
		{
			ScreenManager::advance(p_nextState[p_selector]);
		}
		return true;
	}

	return false;
}

void MainMenuScreen::update()
{

}

void MainMenuScreen::draw(sf::RenderTarget& window)
{
	const sf::Font& font = GameContext::getFont("VCR_OSD_MONO");

	sf::Text laddleText(font, "LADDLE", 120);
	{
		laddleText.setLetterSpacing(2.0f);
		auto lbounds = laddleText.getLocalBounds();
		laddleText.setOrigin(lbounds.position + lbounds.size / 2.0f);
		laddleText.setPosition({window.getSize().x / 2.0f, LADDLE_TEXT_Y_POSITION});
	}
	
	sf::Text playText(font, "PLAY", 60);
	sf::Text aboutText(font, "ABOUT", 60);
	sf::Text settingsText(font, "SETTINGS", 60);
	sf::Text exitText(font, "EXIT", 60);
	sf::Text testText(font, "TEST", 60);
	{
		playText.setPosition({window.getSize().x / 4.0f, PLAY_TEXT_Y_POSITION});
		aboutText.setPosition({window.getSize().x / 4.0f, ABOUT_TEXT_Y_POSITION});
		settingsText.setPosition({window.getSize().x / 4.0f, SETTINGS_TEXT_Y_POSITION});
		exitText.setPosition({window.getSize().x / 4.0f, EXIT_TEXT_Y_POSITION});
		testText.setPosition({window.getSize().x / 4.0f, TEST_TEXT_Y_POSITION});
	}

	sf::Text selectorText(font, ">", 60);
	{
		auto selectorYPosition = p_selector * 80.0f + 300.0f;
		auto lbounds = selectorText.getLocalBounds();
		selectorText.setPosition({window.getSize().x / 4.0f - 2 * lbounds.size.x, selectorYPosition});
	}

	window.draw(laddleText);
	window.draw(playText);
	window.draw(aboutText);
	window.draw(settingsText);
	window.draw(exitText);
	window.draw(testText);
	window.draw(selectorText);
}