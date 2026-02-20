#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "ui/Tile.hpp"

#include "clocks/ShakeClock.hpp"

constexpr auto WORD_LENGTH = 5;

class Row : public sf::Drawable, public sf::Transformable
{
public:
	// default constructor
	explicit Row();

	bool isFull() const;
	bool isEmpty() const;

	sf::Vector2f getAnimatedPosition() const;

	Tile getTileAtIndex(const int& i) const;

	std::array<TileState, WORD_LENGTH> getState() const;
	void check(const std::string& target);
	std::string getWord() const;

	void pushLetter(const char& letter);
	char popLetter();
	void reset();
	void resetState();

	void shake();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states [[maybe_unused]]) const override;

private:
	std::array<Tile, WORD_LENGTH> p_tiles;
	int p_iterator = 0;

	ShakeClock p_shakeClock;

	float p_getShakeDisplacement() const;
	void p_drawTileRect(sf::RenderTarget& target, sf::RenderStates states [[maybe_unused]]) const;
};