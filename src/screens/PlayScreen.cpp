#include <iostream>

#include "screens/PlayScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/centerTextInRect.hpp"

bool PlayScreen::handleInput(const sf::Event& event)
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
		if (p_rowStack.top().isEmpty())
		{
			p_rowStack.pop();
		}
		else
		{
			p_rowStack.top().popLetter();
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_ENTER))
	{
		if (p_rowStack.top().isFull()) 
		{
			p_rowStack.top().check(p_answer);

			Row newRow;
			p_rowStack.push(newRow);
		}
		else
		{
			p_rowStack.top().shake();
		}
		captured = true;
	}

	
	if (event.is<sf::Event::TextEntered>())
	{
		auto letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (!p_rowStack.top().isFull())
			{
				p_rowStack.top().pushLetter(letter);
			}
		}
		captured = true;
	}
	
	ResourceManager::clearActions();

	return captured;
}

void PlayScreen::update()
{
	p_rowStack.top().update();
}

void PlayScreen::draw(sf::RenderTarget& window)
{
	window.draw(p_rowStack.top());
}