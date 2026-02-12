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
	initialRow.setPosition(100.0f, 100.0f);
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
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::TEST_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_BACKSPACE))
	{
		if (p_rowStack.back().isEmpty() && p_rowStack.size() != 1)
		{
			p_rowStack.pop_back();
			p_rowStack.back().resetState();
		}
		else
		{
			p_rowStack.back().popLetter();
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_ENTER))
	{
		
		if (p_rowStack.back().isFull() && binarySearch(ResourceManager::lexicon.cbegin(), ResourceManager::lexicon.cend(), p_rowStack.back().getWord())) 
		{
			auto path = solve(ResourceManager::adjList, ResourceManager::lexicon, p_rowStack.back().getWord(), p_answer);
			p_rowStack.back().check(p_answer);

			Row newRow;
			newRow.setPosition(p_rowStack.back().getPosition().x, p_rowStack.back().getPosition().y + 90);
			p_rowStack.push_back(newRow);
		}
		else
		{
			p_rowStack.back().shake();
		}
		captured = true;
	}

	
	if (event.is<sf::Event::TextEntered>())
	{
		auto letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (!p_rowStack.back().isFull())
			{
				p_rowStack.back().pushLetter(letter);
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
	for (const Row& row : p_rowStack)
	{
		window.draw(row);
	}
}