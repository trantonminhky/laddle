#pragma once
#include <SFML/System.hpp>

struct ShakeClock
{
	static constexpr sf::Time SHAKE_DURATION = sf::seconds(0.5f);
	static constexpr sf::Time SHAKE_STRENGTH = sf::seconds(50.0f);
	static constexpr sf::Time SHAKE_AMPLITUDE = sf::seconds(10.0f);

	bool toggle = false;
	sf::Clock clock;
};