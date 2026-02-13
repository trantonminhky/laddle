#include "app/Program.hpp"
#include "app/solve.hpp"

#include "managers/ResourceManager.hpp"

#include "screens/MainMenuScreen.hpp"

#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

void Program::run()
{
	sf::RenderWindow window(sf::VideoMode({1200, 800}), "poop");

	ResourceManager::init();

	p_screenManager = std::make_unique<ScreenManager>();
	p_screenManager->init();

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>() || p_screenManager->shouldExit())
				window.close();
			p_screenManager->handleInput(*event);
		}
		p_screenManager->update();

		window.clear();
		p_screenManager->draw(window);
		window.display();
	}
}