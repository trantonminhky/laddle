#include "app/Program.hpp"
#include "app/solve.hpp"

#include "contexts/GameContext.hpp"

#include "screens/MainMenuScreen.hpp"

#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

void Program::p_loadFromTxt()
{
	std::ifstream fin("assets/lexicon/words.txt");
	std::string input;
	while (getline(fin, input))
	{
		p_wordList.push_back(input);
	}
	fin.close();
	fin.open("assets/lexicon/adj_list.txt");
	for (int i = 0; getline(fin, input); i++)
	{
		Neighbor neighbors = splitToInteger(input, ' ');
		AdjacencyListEntry entry = AdjacencyListEntry(i, neighbors);
		p_adjList.push_back(entry);
	}
}

void Program::p_init()
{
	p_loadFromTxt();
}

Program::Program(ProgramFlags flags) : p_flags(flags)
{
	p_init();
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
			auto result = solve(p_adjList, p_wordList, p_flags.solveFlagSrc, p_flags.solveFlagDest);
			for (const int& entry : result)
			{
				std::cout << p_wordList[entry] << " ";
			}
			std::cout << '\n';
			break;
		}
		
		case Mode::GAME:
		{
			sf::RenderWindow window(sf::VideoMode({1200, 800}), "poop");

			GameContext::init();

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