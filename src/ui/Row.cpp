#include "ui/Row.hpp"
#include "helper/swag_assert.hpp"

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
		result[i] = p_tiles[i].getLetter();
	}
	return result;
}