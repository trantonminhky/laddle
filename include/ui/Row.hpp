#pragma once
#include "ui/Tile.hpp"
#include <SFML/System.hpp>

constexpr int WORD_LENGTH = 5;

class Row
{
public:
	explicit Row() = default;

	bool isFull() const;

	sf::Vector2f getPosition() const;
	void setPosition(const float& x, const float& y);

	Tile getTileAtIndex(const int& i);

	std::array<TileState, WORD_LENGTH> getState() const;
	void check(const std::string& target);
	std::string getWord() const;
	void appendLetter(const char& letter);
	void reset();

private:
	std::array<Tile, WORD_LENGTH> p_tiles;
	int p_iterator = 0;

	sf::Vector2f p_position = {0.0f, 0.0f};
};