#include "app/Program.hpp"
#include "app/solve.hpp"

#include "managers/ResourceManager.hpp"

#include "screens/MainMenuScreen.hpp"

#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

Program::Program(ProgramFlags flags) : p_flags(flags)
{
	std::cout << "Program init\n";
}

void Program::run()
{
	switch (p_flags.mode)
	{
		case Mode::NONE:
		case Mode::HELP:
		{
			std::cout << "\t-h\t-\tShow list of options\n\t-s\t-\tSolve word ladder\n\t-g\t-\tStart Laddle\n";
			break;
		}

		case Mode::SOLVE:
		{
			auto result = solve(ResourceManager::adjList, ResourceManager::lexicon, p_flags.solveFlagSrc, p_flags.solveFlagDest);
			for (const int& entry : result)
			{
				std::cout << ResourceManager::lexicon[entry] << " ";
			}
			std::cout << '\n';
			break;
		}
		
		case Mode::GAME:
		{
			sf::RenderWindow window(sf::VideoMode({1200, 800}), "poop");

			ResourceManager::init();

			p_screenManager = std::make_unique<ScreenManager>();
			p_screenManager->init();

			while (window.isOpen())
			{
				while (const std::optional event = window.pollEvent())
				{
					if (event->is<sf::Event::Closed>() || p_screenManager->shouldExit()) window.close();
					p_screenManager->handleInput(*event);
				}
				p_screenManager->update();
				
				window.clear();
				p_screenManager->draw(window);
				window.display();
			}
			break;
		}
	}
}