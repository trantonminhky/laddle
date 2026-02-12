#include <iostream>
#include <fstream>

#include "screens/PlayScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/splitToInteger.hpp"
#include "helper/centerTextInRect.hpp"

PlayScreen::PlayScreen() : BaseScreen()
{
	Row initialRow;
	initialRow.setPosition(300.0f, 300.0f);
	p_rowStack.push_back(initialRow);

	std::ifstream fin("assets/lexicon/words.txt");
	std::string input;
	while (getline(fin, input))
	{
		p_lexicon.insert(input);
	}
	fin.close();
	fin.open("assets/lexicon/adj_list.txt");
	for (int i = 0; getline(fin, input); i++)
	{
		Neighbor neighbors = splitToInteger(input, ' ');
		AdjacencyListEntry entry = AdjacencyListEntry(i, neighbors);
		p_adjList.push_back(entry);
	}

	// TO-DO: IMPLEMENT RANDOM ANSWER WORDS
	p_answer = "maker";
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
		}
		else
		{
			p_rowStack.back().popLetter();
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::TEST_ENTER))
	{
		if (p_rowStack.back().isFull() && p_lexicon.find(p_rowStack.back().getWord()) != p_lexicon.cend()) 
		{
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