#pragma once
#include "ui/Tile.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "clocks/ShakeClock.hpp"

constexpr int WORD_LENGTH = 5;

class Row : public sf::Drawable
{
public:
	// default constructor
	explicit Row();

	bool isFull() const;
	bool isEmpty() const;

	sf::Vector2f getPosition() const;
	sf::Vector2f getBasePosition() const;
	sf::Vector2f getAnimatedPosition() const;
	void setPosition(const float& x, const float& y);

	Tile getTileAtIndex(const int& i) const;

	std::array<TileState, WORD_LENGTH> getState() const;
	void check(const std::string& target);
	std::string getWord() const;

	void pushLetter(const char& letter);
	char popLetter();
	void reset();

	void shake();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::array<Tile, WORD_LENGTH> p_tiles;
	int p_iterator = 0;

	sf::Vector2f p_position = {0.0f, 0.0f};

	ShakeClock shakeClock;
};