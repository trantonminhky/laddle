#include <iostream>

#include "screens/InstructionScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/splitString.hpp"
#include "helper/linebreak.hpp"

constexpr sf::Vector2f MAIN_TEXT_POSITION = {100.0f, 100.0f};

constexpr auto ARROW_TEXT_FONT_SIZE = 50;
constexpr sf::Vector2f LEFT_ARROW_TEXT_POSITION = {100.0f, 700.0f};
constexpr sf::Vector2f RIGHT_ARROW_TEXT_POSITION = {1100.0f, 700.0f};

bool InstructionScreen::handleInput(const sf::Event &event)
{
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::INSTRUCTION_MOVE_NEXT_PAGE))
	{
		if (p_iterator < MAX_INSTRUCTION_PAGES - 1)
		{
			p_iterator++;
			captured = true;
		}
	}
	else if (ResourceManager::hasAction(GameAction::INSTRUCTION_MOVE_PREVIOUS_PAGE))
	{
		if (p_iterator > 0)
		{
			p_iterator--;
			captured = true;
		}
	}
	else if (ResourceManager::hasAction(GameAction::INSTRUCTION_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}

	ResourceManager::clearActions();
	return captured;
}

void InstructionScreen::update()
{

}

void InstructionScreen::p_drawText(sf::RenderTarget &window, const sf::Font& font) const
{
	InstructionPage currentPage = INSTRUCTION_PAGES[p_iterator];
	auto currentPageTextTokens = splitString(currentPage.text, '\n');
	std::string currentPageText;
	
	for (const auto& token : currentPageTextTokens)
	{
		currentPageText += linebreak(token, currentPage.lineWidth);
		currentPageText += '\n';
	}

	sf::Text mainText(font, currentPageText, currentPage.fontSize);
	mainText.setPosition(MAIN_TEXT_POSITION);
	window.draw(mainText);
}

void InstructionScreen::p_drawArrow(sf::RenderTarget& window, const sf::Font& font) const
{
	if (p_iterator > 0)
	{
		sf::Text leftArrowText(font, "<", ARROW_TEXT_FONT_SIZE);
		leftArrowText.setPosition(LEFT_ARROW_TEXT_POSITION);
		window.draw(leftArrowText);
	}

	if (p_iterator < MAX_INSTRUCTION_PAGES - 1)
	{
		sf::Text rightArrowText(font, ">", ARROW_TEXT_FONT_SIZE);
		rightArrowText.setPosition(RIGHT_ARROW_TEXT_POSITION);
		window.draw(rightArrowText);
	}
}

void InstructionScreen::draw(sf::RenderTarget &window) const
{
	const sf::Font &font = ResourceManager::getFont(Font::VCR_OSD_MONO);

	p_drawText(window, font);
	p_drawArrow(window, font);
}