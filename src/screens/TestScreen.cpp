#include <iostream>

#include "screens/TestScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/centerTextInRect.hpp"

bool TestScreen::handleInput(const sf::Event& event)
{
	if (p_ignoreFirstFrame)
	{
		p_ignoreFirstFrame = false;
		return false;
	}
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::TEST_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_BACKSPACE))
	{
		p_row.popLetter();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_ENTER))
	{
		if (p_row.isFull()) 
		{
			std::cout << p_row.getWord() << '\n';
			p_row.reset();
		}
		else
		{
			std::cout << "shake" << '\n';
			p_row.shake();
		}
		captured = true;
	}

	
	if (event.is<sf::Event::TextEntered>())
	{
		auto letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (!p_row.isFull())
			{
				p_row.pushLetter(letter);
			}
		}
		captured = true;
	}
	
	ResourceManager::clearActions();

	return captured;
}

void TestScreen::update()
{
	p_row.update();
}

void TestScreen::draw(sf::RenderTarget& window)
{
	const sf::Font& font = ResourceManager::getFont("VCR_OSD_MONO");
	sf::Text allOKText(font, "SFML all OK!", 50);

	window.draw(allOKText);
	window.draw(p_row);
}