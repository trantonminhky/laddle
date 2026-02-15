#pragma once
#include "managers/ResourceManager.hpp"
#include <SFML/Graphics.hpp>

// abstract class for a screen
class BaseScreen
{
public:
	explicit BaseScreen() = default;

	virtual bool handleInput(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& window) const = 0;

	virtual ~BaseScreen() = default;
};