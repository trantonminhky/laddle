#include "ui/Tile.hpp"

#include "managers/ResourceManager.hpp"

#include "helper/centerTextInRect.hpp"

constexpr auto TILE_SIDE_LENGTH = 80.0f;

constexpr auto YELLOW_COLOR = sf::Color(255, 252, 114);
constexpr auto GREEN_COLOR = sf::Color(127, 163, 92);

constexpr auto TILE_LETTER_TEXT_FONT_SIZE = 80;

void Tile::draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const
{
	const sf::Font& font = ResourceManager::getFont(Font::VCR_OSD_MONO);

	sf::RectangleShape tileRect({TILE_SIDE_LENGTH, TILE_SIDE_LENGTH});
	tileRect.setPosition(getPosition());
	
	if (p_state == TileState::MISPLACED)
	{
		tileRect.setFillColor(YELLOW_COLOR);
	}
	else if (p_state == TileState::CORRECT)
	{
		tileRect.setFillColor(GREEN_COLOR);
	}

	target.draw(tileRect);

	sf::Text tileLetterText(font, p_letter, TILE_LETTER_TEXT_FONT_SIZE);
	tileLetterText.setFillColor(sf::Color::Black);
	centerTextInRect(tileLetterText, tileRect);

	target.draw(tileLetterText);
}

TileState Tile::getState() const
{
	return p_state;
}

void Tile::setState(const TileState& newState)
{
	p_state = newState;
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

void Tile::reset()
{
	clearLetter();
	p_state = TileState::NONE;
}