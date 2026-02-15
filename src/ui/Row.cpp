#include <cmath>
#include <iostream>

#include "ui/Row.hpp"

#include "managers/ResourceManager.hpp"

#include "helper/swag_assert.hpp"
#include "helper/centerTextInRect.hpp"

constexpr auto ENGLISH_ALPHABET_SIZE = 26;

constexpr auto YELLOW_COLOR = sf::Color(255, 252, 114);
constexpr auto GREEN_COLOR = sf::Color(127, 163, 92);

constexpr auto TILE_LETTER_TEXT_FONT_SIZE = 80;
constexpr auto TILE_HORIZONTAL_SPACING = 90;

float Row::p_getShakeDisplacement() const
{
	auto x = p_shakeClock.SHAKE_AMPLITUDE.asSeconds() * std::sin(p_position.x * p_shakeClock.SHAKE_STRENGTH.asSeconds() * p_shakeClock.clock.getElapsedTime().asSeconds());
	return x;
}

Row::Row()
{
	p_shakeClock.clock.reset();
}

bool Row::isFull() const
{
	return p_iterator >= WORD_LENGTH;
}

bool Row::isEmpty() const
{
	return p_iterator == 0;
}

sf::Vector2f Row::getBasePosition() const
{
	return p_position;
}

sf::Vector2f Row::getAnimatedPosition() const
{
	auto shakeDisplacement = p_getShakeDisplacement();
	return {p_position.x + shakeDisplacement, p_position.y};
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
	std::array<int, ENGLISH_ALPHABET_SIZE> freq;
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
	p_shakeClock.toggle = true;
	p_shakeClock.clock.restart();
}

void Row::update()
{
	auto currentTilePosition = getPosition();
	for (int i = 0; i < WORD_LENGTH; i++)
	{
		p_tiles[i].setPosition(currentTilePosition);
		currentTilePosition.x += TILE_HORIZONTAL_SPACING;
	}

	if (!p_shakeClock.toggle) return;
	if (p_shakeClock.clock.getElapsedTime() >= p_shakeClock.SHAKE_DURATION)
	{
		p_shakeClock.toggle = false;
		p_shakeClock.clock.reset();
	}
}

void Row::draw(sf::RenderTarget& target, sf::RenderStates states [[maybe_unused]]) const
{
	for (int i = 0; i < WORD_LENGTH; i++)
	{
		target.draw(p_tiles[i]);
	}
}