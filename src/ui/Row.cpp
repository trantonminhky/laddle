#include <cmath>
#include <iostream>

#include "ui/Row.hpp"

#include "managers/ResourceManager.hpp"

#include "helper/swag_assert.hpp"
#include "helper/centerTextInRect.hpp"

Row::Row()
{
	shakeClock.clock.reset();
}

bool Row::isFull() const
{
	return p_iterator >= WORD_LENGTH;
}

bool Row::isEmpty() const
{
	return p_iterator == 0;
}

sf::Vector2f Row::getPosition() const
{
	if (shakeClock.toggle) return getAnimatedPosition();
	else return getBasePosition();
}

sf::Vector2f Row::getBasePosition() const
{
	return p_position;
}

sf::Vector2f Row::getAnimatedPosition() const
{
	auto x = shakeClock.SHAKE_AMPLITUDE.asSeconds() * std::sin(p_position.x * shakeClock.SHAKE_STRENGTH.asSeconds() * shakeClock.clock.getElapsedTime().asSeconds());
	return {p_position.x + x, p_position.y};
}

void Row::setPosition(const float& x, const float& y)
{
	p_position.x = x;
	p_position.y = y;
}

void Row::setPosition(const sf::Vector2f& vecf)
{
	p_position = vecf;
}

Tile Row::getTileAtIndex(const int& i) const
{
	swag_assert(i >= 0 && i < WORD_LENGTH);
	return p_tiles[i];
}

std::array<TileState, WORD_LENGTH> Row::getState() const
{
	std::array<TileState, WORD_LENGTH> states;
	for (int i = 0; i < WORD_LENGTH; i++)
	{
		states[i] = p_tiles[i].getState();
	}

	return states;
}

void Row::check(const std::string& target)
{
	std::array<int, 26> freq;
	freq.fill(0);

	for (int i = 0; i < WORD_LENGTH; i++)
	{
		Tile& tile = p_tiles[i];
		const char targetLetter = target[i];

		if (tile.getLetter() == targetLetter) tile.setState(TileState::CORRECT);
		else freq[targetLetter - 'a']++;
	}

	for (Tile& tile : p_tiles)
	{
		if (tile.getState() == TileState::CORRECT) continue;
		if (freq[tile.getLetter() - 'a'])
		{
			tile.setState(TileState::MISPLACED);
			freq[tile.getLetter() - 'a']--;
		}
	}
}

std::string Row::getWord() const
{
	
	std::string result = "STUPI";
	for (int i = 0; i < WORD_LENGTH; i++)
	{
		char letter = p_tiles[i].getLetter();
		swag_assert(letter != '\x00');
		result[i] = letter;
	}
	return result;
}

void Row::pushLetter(const char& letter)
{
	swag_assert(letter >= 'a' && letter <= 'z');
	swag_assert(p_iterator < WORD_LENGTH);

	p_tiles[p_iterator].setLetter(letter);
	p_iterator++;
}

char Row::popLetter()
{
	if (p_iterator > 0) p_iterator--;
	auto popped = getTileAtIndex(p_iterator).getLetter();
	p_tiles[p_iterator].clearLetter();
	return popped;
}

void Row::reset()
{
	for (Tile& tile : p_tiles)
	{
		tile.reset();
	}
	p_iterator = 0;
}

void Row::resetState()
{
	for (Tile& tile : p_tiles)
	{
		tile.setState(TileState::NONE);
	}
}

void Row::shake()
{
	shakeClock.toggle = true;
	shakeClock.clock.restart();
}

void Row::update()
{
	if (!shakeClock.toggle) return;
	if (shakeClock.clock.getElapsedTime() >= shakeClock.SHAKE_DURATION)
	{
		shakeClock.toggle = false;
		shakeClock.clock.reset();
	}
}

void Row::draw(sf::RenderTarget& target, sf::RenderStates states [[maybe_unused]]) const
{
	sf::Vector2f currentTilePosition = getPosition();
	const sf::Font& font = ResourceManager::getFont("VCR_OSD_MONO");
	for (int i = 0; i < WORD_LENGTH; i++)
	{
		sf::RectangleShape tileRect({80.0f, 80.f});
		tileRect.setPosition(currentTilePosition);
		if (getTileAtIndex(i).getState() == TileState::MISPLACED)
		{
			tileRect.setFillColor(sf::Color(255, 252, 114));
		}
		else if (getTileAtIndex(i).getState() == TileState::CORRECT)
		{
			tileRect.setFillColor(sf::Color(127, 163, 92));
		}
		else
		{
			tileRect.setFillColor(sf::Color(255, 255, 255));
		}

		auto tileLetter = getTileAtIndex(i).getLetter();
		sf::Text tileLetterText(font, tileLetter, 80);
		tileLetterText.setFillColor(sf::Color::Black);
		centerTextInRect(tileLetterText, tileRect);

		target.draw(tileRect);
		target.draw(tileLetterText);

		currentTilePosition.x += 90;
	}
}