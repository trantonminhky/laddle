#include <iostream>
#include <fstream>

#include "app/solve.hpp"

#include "screens/PlayScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "helper/splitToInteger.hpp"
#include "helper/centerTextInRect.hpp"
#include "helper/vecrand.hpp"
#include "helper/hammingDistance.hpp"

#include "algo/binarySearch.hpp"

constexpr auto MESSAGE_TEXT_FONT_SIZE = 50;

constexpr auto ROW_X_POSITION = 350.0f;
constexpr auto ROW_CENTER_Y_POSITION = 350.0f;
constexpr auto ROW_VERTICAL_SPACING = 90.0f;

constexpr auto ELLIPSIS_TEXT_FONT_SIZE = 50;
constexpr auto ELLIPSIS_TEXT_X_POSITION = 800.0f;
constexpr auto ELLIPSIS_TEXT_UP_Y_POSITION = 100.0f;
constexpr auto ELLIPSIS_TEXT_DOWN_Y_POSITION = 700.0f;

constexpr auto MAXIMUM_ROW_COUNT_PER_SIDE = 3;

void PlayScreen::p_generateSourceAndAnswer()
{
	p_answer = vecrand(ResourceManager::concordance);
	do
	{
		p_source = vecrand(ResourceManager::concordance);
	} while (solve(ResourceManager::adjList, ResourceManager::lexicon, p_source, p_answer).empty());
}

void PlayScreen::p_initFirstGuess()
{
	for (const char &c : p_source)
	{
		p_rowStack.back().pushLetter(c);
	}
	p_rowStack.back().check(p_answer);
}

void PlayScreen::p_pushRow()
{
	Row newRow;

	p_rowStack.push_back(newRow);
	p_iterator++;
}

void PlayScreen::p_popRow()
{
	p_rowStack.pop_back();
	p_iterator--;

	p_rowStack.back().resetState();
}

void PlayScreen::p_drawMessage(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text messageText(font, p_message, MESSAGE_TEXT_FONT_SIZE);
	window.draw(messageText);
}

void PlayScreen::p_drawRows(sf::RenderTarget& window, int start, int end) const
{
	int stackSize = p_rowStack.size();
	for (int i = start; i < end; i++)
	{
		if (i >= 0 && i < stackSize)
		{
			window.draw(p_rowStack[i]);
		}
	}
}

void PlayScreen::p_drawEllipses(sf::RenderTarget& window, const sf::Font& font, int start, int end) const
{
	int stackSize = p_rowStack.size();
	if (start > 0)
	{
		sf::Text ellipsisUpText(font, "...", ELLIPSIS_TEXT_FONT_SIZE);
		ellipsisUpText.setPosition({ELLIPSIS_TEXT_X_POSITION, ELLIPSIS_TEXT_UP_Y_POSITION});
		window.draw(ellipsisUpText);
	}

	if (end < stackSize - 1)
	{
		sf::Text ellipsisDownText(font, "...", ELLIPSIS_TEXT_FONT_SIZE);
		ellipsisDownText.setPosition({ELLIPSIS_TEXT_X_POSITION, ELLIPSIS_TEXT_DOWN_Y_POSITION});
		window.draw(ellipsisDownText);
	}
}

PlayScreen::PlayScreen() : BaseScreen()
{
	p_pushRow();

	p_generateSourceAndAnswer();
	p_initFirstGuess();
	p_pushRow();

	auto solvedPath = solve(ResourceManager::adjList, ResourceManager::lexicon, p_source, p_answer);
	for (const auto &e : solvedPath)
	{
		std::cout << ResourceManager::lexicon[e] << ' ';
	}
	std::cout << std::endl;

	p_message = "go on...";
}

bool PlayScreen::handleInput(const sf::Event &event)
{
	// the first frame must be ignored to prevent input leaking from main menu
	if (p_ignoreFirstFrame)
	{
		p_ignoreFirstFrame = false;
		return false;
	}

	Row &rowStackTop = p_rowStack.back();
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
			if (rowStackTop.isEmpty() && p_rowStack.size() > 2) p_popRow();
			else
			{
				rowStackTop.popLetter();
				ResourceManager::playSoundBackspaceLetter();
			}
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_ENTER))
	{
		if (p_winnar)
		{
			ResourceManager::playSoundShakeRow();
			p_message = "kid you have alr won";
		}
		else if (p_detachedHead)
		{
			ResourceManager::playSoundShakeRow();
			p_message = "kid get back to your row";
		}
		else if (!rowStackTop.isFull())
		{
			rowStackTop.shake();
			ResourceManager::playSoundShakeRow();
			p_message = "kid that ain't a 5 letter word";
		}
		else if (hammingDistance(rowStackTop.getWord(), (*(p_rowStack.cend() - 2)).getWord()) != 1)
		{
			rowStackTop.shake();
			ResourceManager::playSoundShakeRow();
			p_message = "kid that will not make a ladder";
		}
		else if (!binarySearch(ResourceManager::lexicon.cbegin(), ResourceManager::lexicon.cend(), rowStackTop.getWord()))
		{
			rowStackTop.shake();
			ResourceManager::playSoundShakeRow();
			p_message = "kid that ain't an english word";
		}
		else if (solve(ResourceManager::adjList, ResourceManager::lexicon, rowStackTop.getWord(), p_answer).empty())
		{
			rowStackTop.shake();
			ResourceManager::playSoundShakeRow();
			p_message = "you are COOKED if you continue with this word";
		}
		else
		{
			rowStackTop.check(p_answer);
			if (rowStackTop.getWord() == p_answer)
			{
				p_winnar = true;
				p_message = "winnar!!!";
			}
			else
			{
				p_pushRow();
				p_message = "go on...";
			}
			ResourceManager::playSoundInputRow();
		}
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_MOVE_PREVIOUS_ROW))
	{
		if (p_iterator > 0)
		{
			p_iterator--;
			p_detachedHead = true;
			ResourceManager::playSoundMoveRow();
		}
	}
	else if (ResourceManager::hasAction(GameAction::PLAY_MOVE_NEXT_ROW))
	{
		int stackSize = p_rowStack.size();
		if (p_iterator < stackSize - 1)
		{
			if (p_iterator == stackSize - 2)
				p_detachedHead = false;
			p_iterator++;
			ResourceManager::playSoundMoveRow();
		}
	}

	if (event.is<sf::Event::TextEntered>() && !p_detachedHead && !p_winnar)
	{
		auto letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (!rowStackTop.isFull())
			{
				rowStackTop.pushLetter(letter);
				ResourceManager::playSoundInputLetter();
			}
		}
		captured = true;
	}

	ResourceManager::clearActions();
	return captured;
}

void PlayScreen::update()
{
	auto start = p_iterator - MAXIMUM_ROW_COUNT_PER_SIDE;
	auto end = p_iterator + MAXIMUM_ROW_COUNT_PER_SIDE + 1;
	int stackSize = p_rowStack.size();

	for (int i = start; i < end; i++)
	{
		if (i >= 0 && i < stackSize)
		{
			p_rowStack[i].setPosition({ROW_X_POSITION, ROW_CENTER_Y_POSITION + ROW_VERTICAL_SPACING * (i - p_iterator)});
		}
	}
	
	for (Row& row : p_rowStack)
	{
		row.update();
	}
}

void PlayScreen::draw(sf::RenderTarget& window) const
{
	const sf::Font &font = ResourceManager::getFont(Font::VCR_OSD_MONO);
	
	auto rowDrawingStartIndex = p_iterator - MAXIMUM_ROW_COUNT_PER_SIDE;
	auto rowDrawingEndIndex = p_iterator + MAXIMUM_ROW_COUNT_PER_SIDE + 1;
	
	p_drawRows(window, rowDrawingStartIndex, rowDrawingEndIndex);
	p_drawEllipses(window, font, rowDrawingStartIndex, rowDrawingEndIndex);
	p_drawMessage(window, font);
}