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
			std::cout << "\t-h\t-\tShow list of options\n\t-s\t-\tSolve word ladder\n";
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
			screenPtr = std::make_unique<MainMenuScreen>(window);

			GameContext::init();

			while (window.isOpen())
			{
				while (const std::optional event = window.pollEvent())
				{
					if (event->is<sf::Event::Closed>()) window.close();
					screenPtr->handleInput(*event);
				}
				screenPtr->update();
				screenPtr->draw();
			}
			break;
		}
	}
}