#include <iostream>

#include "screens/AboutScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/splitString.hpp"
#include "helper/linebreak.hpp"

bool AboutScreen::handleInput(const sf::Event &event)
{
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::ABOUT_MOVE_NEXT_PAGE))
	{
		if (p_iterator < MAX_ABOUT_PAGES - 1)
		{
			p_iterator++;
			captured = true;
		}
	}
	else if (ResourceManager::hasAction(GameAction::ABOUT_MOVE_PREVIOUS_PAGE))
	{
		if (p_iterator > 0)
		{
			p_iterator--;
			captured = true;
		}
	}
	else if (ResourceManager::hasAction(GameAction::ABOUT_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}

	ResourceManager::clearActions();
	return captured;
}

void AboutScreen::update()
{
}

void AboutScreen::p_drawText(sf::RenderTarget &window, const sf::Font& font) const
{
	AboutPage currentPage = ABOUT_PAGES[p_iterator];
	auto currentPageTextTokens = splitString(currentPage.text, '\n');
	std::string currentPageText;
	
	for (const auto& token : currentPageTextTokens)
	{
		currentPageText += linebreak(token, currentPage.lineWidth);
		currentPageText += '\n';
	}
	sf::Text mainText(font, currentPageText, currentPage.fontSize);
	mainText.setPosition({100.0f, 100.0f});
	window.draw(mainText);
}

void AboutScreen::p_drawArrow(sf::RenderTarget& window, const sf::Font& font) const
{
	if (p_iterator > 0)
	{
		sf::Text leftArrowText(font, "<", 50);
		leftArrowText.setPosition({100, 700});
		window.draw(leftArrowText);
	}

	if (p_iterator < MAX_ABOUT_PAGES - 1)
	{
		sf::Text rightArrowText(font, ">", 50);
		rightArrowText.setPosition({1100, 700});
		window.draw(rightArrowText);
	}
}

void AboutScreen::draw(sf::RenderTarget &window) const
{
	const sf::Font &font = ResourceManager::getFont(Font::VCR_OSD_MONO);

	p_drawText(window, font);
	p_drawArrow(window, font);
}