#include <fstream>

#include "managers/ResourceManager.hpp"

#include "helper/splitToInteger.hpp"

namespace ResourceManager
{
	GameState currentState = GameState::MAIN_MENU;
	std::unique_ptr<FontManager> fontManagerPtr;
	std::unique_ptr<ActionManager> actionManagerPtr;
	std::unique_ptr<AudioManager> audioManagerPtr;
	std::vector<std::string> lexicon;
	std::vector<std::string> concordance;
	std::vector<AdjacencyListEntry> adjList;

	void loadLexicon()
	{
		// lexicon is the list of valid english words
		std::ifstream fin("assets/lexicon/lexicon.txt");
		std::string input;
		while (getline(fin, input))
		{
			lexicon.push_back(input);
		}
		fin.close();
	}

	void loadConcordance()
	{
		// concordance is a list of valid english words eligible to be the initial guess and the answer. indeed lexicon is a superset of concordance
		std::ifstream fin("assets/lexicon/concordance.txt");
		std::string input;
		while (getline(fin, input))
		{
			concordance.push_back(input);
		}
		fin.close();
	}

	void loadAdjList()
	{
		// adj list of the bidirectional graph where two words are adjacent if their hamming distance is 1
		std::ifstream fin("assets/lexicon/adj_list.txt");
		std::string input;
		for (int i = 0; getline(fin, input); i++)
		{
			Neighbor neighbors = splitToInteger(input, ' ');
			AdjacencyListEntry entry = AdjacencyListEntry(i, neighbors);
			adjList.push_back(entry);
		}
		fin.close();
	}

	void loadAssets()
	{
		loadLexicon();
		loadConcordance();
		loadAdjList();
	}

	void init()
	{
		fontManagerPtr = std::make_unique<FontManager>();
		fontManagerPtr->init();

		actionManagerPtr = std::make_unique<ActionManager>();

		audioManagerPtr = std::make_unique<AudioManager>();
		audioManagerPtr->init();

		loadAssets();
	}
}