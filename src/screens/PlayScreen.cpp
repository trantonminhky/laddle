#include <iostream>
#include <fstream>

#include <app/solve.hpp>

#include "screens/PlayScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/splitToInteger.hpp"
#include "algo/binarySearch.hpp"
#include "helper/centerTextInRect.hpp"
#include "helper/vecrand.hpp"

PlayScreen::PlayScreen() : BaseScreen()
{
	Row initialRow;
	initialRow.setPosition(350.0f, 350.0f);
	p_rowStack.push_back(initialRow);

	p_answer = vecrand(ResourceManager::lexicon);
}

bool PlayScreen::handleInput(const sf::Event& event)
{
	if (p_ignoreFirstFrame)
	{
		p_ignoreFirstFrame = false;
		return false;
	}
	Row& rowStackTop = p_rowStack.back();
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::TEST_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_BACKSPACE))
	{
		if (rowStackTop.isEmpty() && p_rowStack.size() != 1)
		{
			p_rowStack.pop_back();
			// do not use rowStackTop here, the stack was popped

			for (Row& row : p_rowStack)
			{
				row.setPosition(row.getPosition().x, row.getPosition().y + 90);
			}

			p_rowStack.back().resetState();
		}
		else
		{
			rowStackTop.popLetter();
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_ENTER))
	{
		if (!rowStackTop.isFull())
		{
			rowStackTop.shake();
			p_message = "kid that ain't a 5 letter word";
		}
		else if (!binarySearch(ResourceManager::lexicon.cbegin(), ResourceManager::lexicon.cend(), rowStackTop.getWord()))
		{
			rowStackTop.shake();
			p_message = "nigga are u illiterate that ain't an english word";
		}
		else if (solve(ResourceManager::adjList, ResourceManager::lexicon, rowStackTop.getWord(), p_answer).empty())
		{
			rowStackTop.shake();
			p_message = "you are COOKED if you continue with this word";
		}
		else
		{
			rowStackTop.check(p_answer);

			for (Row& row : p_rowStack)
			{
				row.setPosition(row.getPosition().x, row.getPosition().y - 90);
			}

			Row newRow;
			// newRow.setPosition(rowStackTop.getPosition().x, rowStackTop.getPosition().y + 90);
			newRow.setPosition(350.0f, 350.0f);
			p_rowStack.push_back(newRow);

			p_message = "Go on...";
		}
		captured = true;
	}

	
	if (event.is<sf::Event::TextEntered>())
	{
		auto letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (!rowStackTop.isFull())
			{
				rowStackTop.pushLetter(letter);
			}
		}
		captured = true;
	}
	
	ResourceManager::clearActions();

	return captured;
}

void PlayScreen::update()
{
	p_rowStack.back().update();
}

void PlayScreen::draw(sf::RenderTarget& window)
{
	const sf::Font& font = ResourceManager::getFont("VCR_OSD_MONO");
	sf::Text messageText(font, p_message, 50);

	for (const Row& row : p_rowStack)
	{
		window.draw(row);
	}
	window.draw(messageText);
}