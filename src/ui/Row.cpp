#include "ui/Row.hpp"
#include "helper/swag_assert.hpp"

bool Row::isFull() const
{
	return p_iterator >= WORD_LENGTH;
}

sf::Vector2f Row::getPosition() const
{
	return p_position;
}

void Row::setPosition(const float& x, const float& y)
{
	p_position.x = x;
	p_position.y = y;
}

Tile Row::getTileAtIndex(const int& i)
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
	int freq[26] = {0};

	for (int i = 0; i < WORD_LENGTH; i++)
	{
		Tile tile = p_tiles[i];
		const char targetLetter = target[i];

		if (tile.getLetter() == targetLetter) tile.setState(TileState::CORRECT);
		else freq[tile.getLetter() - 'a']++;
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
		swag_assert(letter == '\x00');
		result[i] = letter;
	}
	return result;
}

void Row::appendLetter(const char& letter)
{
	swag_assert(letter >= 'a' && letter <= 'z');
	swag_assert(p_iterator < WORD_LENGTH);

	p_tiles[p_iterator].setLetter(letter);
	p_iterator++;
}

void Row::reset()
{
	for (Tile& tile : p_tiles)
	{
		tile.reset();
	}
	p_iterator = 0;
}