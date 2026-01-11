#pragma once
#include "ui/Tile.hpp"

constexpr int WORD_LENGTH = 5;

class Row
{
public:
	Row() = default;

	std::array<TileState, WORD_LENGTH> getState() const;
	void check(const std::string& target);
	std::string getWord() const;

private:
	std::array<Tile, WORD_LENGTH> p_tiles;
};