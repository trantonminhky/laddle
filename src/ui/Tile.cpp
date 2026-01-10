#include "ui/Tile.hpp"

TileState Tile::getState()
{
	return state;
}

void Tile::setState(TileState newState)
{
	state = newState;
}

char Tile::getLetter()
{
	return p_letter;
}

void Tile::clearLetter()
{
	p_letter = '\x00';
}

void Tile::setLetter(char newLetter)
{
	p_letter = newLetter;
}