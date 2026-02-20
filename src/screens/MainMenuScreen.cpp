#include <iostream>

#include "screens/MainMenuScreen.hpp"

#include "helper/centerTextInRect.hpp"

#include "managers/ScreenManager.hpp"

constexpr auto LADDLE_TEXT_Y_POSITION = 100.0f;
constexpr auto LADDLE_TEXT_CONTENT = "LADDLE";
constexpr auto LADDLE_TEXT_FONT_SIZE = 120;
constexpr auto LADDLE_TEXT_LETTER_SPACING = 2.0f;

constexpr auto MENU_OPTIONS_TEXT_FONT_SIZE = 60;
// higher number = text goes left
constexpr auto MENU_OPTIONS_INDENT = 4.0f;
constexpr auto MENU_OPTIONS_FIRST_OPTION_Y_POSITION = 300.0f;
constexpr auto MENU_OPTIONS_VERTICAL_SPACING = 80.0f;

constexpr auto PLAY_TEXT_Y_POSITION = MENU_OPTIONS_FIRST_OPTION_Y_POSITION + MENU_OPTIONS_VERTICAL_SPACING * 0;
constexpr auto INSTRUCTION_TEXT_Y_POSITION = MENU_OPTIONS_FIRST_OPTION_Y_POSITION + MENU_OPTIONS_VERTICAL_SPACING * 1;
constexpr auto SETTINGS_TEXT_Y_POSITION = MENU_OPTIONS_FIRST_OPTION_Y_POSITION + MENU_OPTIONS_VERTICAL_SPACING * 2;
constexpr auto EXIT_TEXT_Y_POSITION = MENU_OPTIONS_FIRST_OPTION_Y_POSITION + MENU_OPTIONS_VERTICAL_SPACING * 3;

constexpr auto SELECTOR_TEXT_FONT_SIZE = 60;
constexpr auto SELECTOR_HORIZONTAL_SPACING = 2.0f;

bool MainMenuScreen::handleInput(const sf::Event& event)
{
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::MAIN_MENU_MOVE_UP))
	{
		p_selector = (p_selector + P_MAIN_MENU_MAX_OPTIONS - 1) % P_MAIN_MENU_MAX_OPTIONS;
		ResourceManager::playSoundMoveMenuOption();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::MAIN_MENU_MOVE_DOWN))
	{
		p_selector = (p_selector + 1) % P_MAIN_MENU_MAX_OPTIONS;
		ResourceManager::playSoundMoveMenuOption();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::MAIN_MENU_SELECT))
	{
		ScreenManager::advance(p_nextState[p_selector]);
		ResourceManager::playSoundSelectMenuOption();
		captured = true;
	}

	ResourceManager::clearActions();
	return captured;
}

void MainMenuScreen::update()
{

}

void MainMenuScreen::p_drawTitle(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text laddleText(font, LADDLE_TEXT_CONTENT, LADDLE_TEXT_FONT_SIZE);
	{
		laddleText.setLetterSpacing(LADDLE_TEXT_LETTER_SPACING);
		auto lbounds = laddleText.getLocalBounds();
		laddleText.setOrigin(lbounds.position + lbounds.size / 2.0f);
		laddleText.setPosition({window.getSize().x / 2.0f, LADDLE_TEXT_Y_POSITION});
	}

	window.draw(laddleText);
}

void MainMenuScreen::p_drawMenuOptions(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text playText(font, "PLAY", MENU_OPTIONS_TEXT_FONT_SIZE);
	sf::Text instructionText(font, "INSTRUCTION", MENU_OPTIONS_TEXT_FONT_SIZE);
	sf::Text settingsText(font, "SETTINGS", MENU_OPTIONS_TEXT_FONT_SIZE);
	sf::Text exitText(font, "EXIT", MENU_OPTIONS_TEXT_FONT_SIZE);
	{
		playText.setPosition({window.getSize().x / MENU_OPTIONS_INDENT, PLAY_TEXT_Y_POSITION});
		instructionText.setPosition({window.getSize().x / MENU_OPTIONS_INDENT, INSTRUCTION_TEXT_Y_POSITION});
		settingsText.setPosition({window.getSize().x / MENU_OPTIONS_INDENT, SETTINGS_TEXT_Y_POSITION});
		exitText.setPosition({window.getSize().x / MENU_OPTIONS_INDENT, EXIT_TEXT_Y_POSITION});
	}

	window.draw(playText);
	window.draw(instructionText);
	window.draw(settingsText);
	window.draw(exitText);
}

void MainMenuScreen::p_drawSelector(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text selectorText(font, ">", SELECTOR_TEXT_FONT_SIZE);
	{
		auto selectorYPosition = p_selector * MENU_OPTIONS_VERTICAL_SPACING + MENU_OPTIONS_FIRST_OPTION_Y_POSITION;
		auto lbounds = selectorText.getLocalBounds();
		selectorText.setPosition({window.getSize().x / MENU_OPTIONS_INDENT - SELECTOR_HORIZONTAL_SPACING * lbounds.size.x, selectorYPosition});
	}

	window.draw(selectorText);
}

void MainMenuScreen::draw(sf::RenderTarget& window) const
{
	const sf::Font& font = ResourceManager::getFont(Font::VCR_OSD_MONO);

	p_drawTitle(window, font);
	p_drawMenuOptions(window, font);
	p_drawSelector(window, font);
}