#include <fstream>

#include "managers/ResourceManager.hpp"

#include "helper/splitToInteger.hpp"

namespace ResourceManager
{
	GameState currentState = GameState::MAIN_MENU;
	std::unique_ptr<FontManager> fontManagerPtr;
	std::unique_ptr<ActionManager> actionManagerPtr;
	std::vector<std::string> lexicon;
	std::vector<std::string> concordance;
	std::vector<AdjacencyListEntry> adjList;

	void loadFromTxt()
	{
		std::ifstream fin("assets/lexicon/lexicon.txt");
		std::string input;
		while (getline(fin, input))
		{
			lexicon.push_back(input);
		}
		fin.close();
		fin.open("assets/lexicon/concordance.txt");
		while (getline(fin, input))
		{
			concordance.push_back(input);
		}
		fin.close();
		fin.open("assets/lexicon/adj_list.txt");
		for (int i = 0; getline(fin, input); i++)
		{
			Neighbor neighbors = splitToInteger(input, ' ');
			AdjacencyListEntry entry = AdjacencyListEntry(i, neighbors);
			adjList.push_back(entry);
		}
	}

	void init()
	{
		fontManagerPtr = std::make_unique<FontManager>();
		fontManagerPtr->init();

		actionManagerPtr = std::make_unique<ActionManager>();

		loadFromTxt();
	}
}