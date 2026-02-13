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

	if (ResourceManager::hasAction(GameAction::PLAY_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_BACKSPACE))
	{
		if (!p_detachedHead)
		{
			if (rowStackTop.isEmpty() && p_rowStack.size() != 1)
			{
				p_rowStack.pop_back();
				p_iterator--;
				// do not use rowStackTop here, the stack was popped
	
				p_rowStack.back().resetState();
			}
			else
			{
				rowStackTop.popLetter();
			}
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_ENTER))
	{
		if (p_detachedHead)
		{
			p_message = "get back to yo row u epstein or sum";
		}
		else if (!rowStackTop.isFull())
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

			Row newRow;

			p_rowStack.push_back(newRow);
			p_iterator++;

			p_message = "Go on...";
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_MOVE_PREVIOUS_ROW))
	{
		if (p_iterator > 0)
		{
			p_iterator--;
			p_detachedHead = true;
		}
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_MOVE_NEXT_ROW))
	{
		int stackSize = p_rowStack.size();
		if (p_iterator < stackSize - 1)
		{
			if (p_iterator == stackSize - 2) p_detachedHead = false;
			p_iterator++;
		}
	}

	
	if (event.is<sf::Event::TextEntered>() && !p_detachedHead)
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

	auto rowDrawingStartIndex = p_iterator - 3;
	auto rowDrawingEndIndex = p_iterator + 4;

	int stackSize = p_rowStack.size();

	for (int i = rowDrawingStartIndex; i < rowDrawingEndIndex; i++)
	{
		if (i >= 0 && i < stackSize)
		{
			p_rowStack[i].setPosition(350.0f, 350.0f + 90 * (i - p_iterator));
			window.draw(p_rowStack[i]);
		}

	}
	window.draw(messageText);
}