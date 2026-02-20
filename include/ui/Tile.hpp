#pragma once
#include <SFML/Graphics.hpp>

enum class TileState
{
	NONE,		// not checked or answer does not have letter
	MISPLACED,	// answer has letter in different tile
	CORRECT		// answer has letter in correct spot
};

// a tile slot holding one character
class Tile : public sf::Transformable, public sf::Drawable
{
public:
	explicit Tile() = default;

	void draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const override;

	TileState getState() const;
	void setState(const TileState& newState);
	char getLetter() const;
	void clearLetter();
	void setLetter(const char& newLetter);
	void reset();

private:
	TileState p_state = TileState::NONE;
	char p_letter = '\x00';
};