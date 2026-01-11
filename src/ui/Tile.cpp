#include "ui/Tile.hpp"

TileState Tile::getState() const
{
	return state;
}

void Tile::setState(const TileState& newState)
{
	state = newState;
}

char Tile::getLetter() const
{
	return p_letter;
}

void Tile::clearLetter()
{
	p_letter = '\x00';
}

void Tile::setLetter(const char& newLetter)
{
	p_letter = newLetter;
}