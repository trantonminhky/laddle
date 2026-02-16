#pragma once

#include "Types.hpp"

#include "managers/FontManager.hpp"
#include "managers/ActionManager.hpp"
#include "managers/AudioManager.hpp"

// ////////////////////////////////////
// GAME STATES
enum class GameState
{
	NONE,
	MAIN_MENU,
	PLAY,
	ABOUT,
	OPTIONS,
	NOT_IMPLEMENTED
};

namespace ResourceManager
{
	extern std::unique_ptr<FontManager> fontManagerPtr;
	extern std::unique_ptr<ActionManager> actionManagerPtr;
	extern std::unique_ptr<AudioManager> audioManagerPtr;
	extern std::vector<std::string> lexicon;
	extern std::vector<std::string> concordance;
	extern std::vector<AdjacencyListEntry> adjList;
	void init();



	// #######################################
	// ############ FONT MANAGER #############
	// #######################################
	template <typename ...Ts>
	const sf::Font& getFont(Ts&&... yuke)
	{
		return fontManagerPtr->get(std::forward<Ts>(yuke)...);
	}



	// #######################################
	// ########### ACTION MANAGER ############
	// #######################################
	template <typename ...Ts>
	void checkActions(Ts&&... yuke)
	{
		actionManagerPtr->checkActions(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	bool hasAction(Ts&&... yuke)
	{
		return actionManagerPtr->hasAction(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	void clearActions(Ts&&... yuke)
	{
		actionManagerPtr->clearActions(std::forward<Ts>(yuke)...);
	}



	// #######################################
	// ############ AUDIO MANAGER ############
	// #######################################
	template <typename ...Ts>
	sf::Sound& getSoundBuffer(Ts&&... yuke)
	{
		return audioManagerPtr->getSound(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	void playSoundInputLetter(Ts&&... yuke)
	{
		audioManagerPtr->playSoundInputLetter(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	void playSoundInputRow(Ts&&... yuke)
	{
		audioManagerPtr->playSoundInputRow(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	void playSoundBackspaceLetter(Ts&&... yuke)
	{
		audioManagerPtr->playSoundBackspaceLetter(std::forward<Ts>(yuke)...);
	}

	template <typename ...Ts>
	void playSoundShakeRow(Ts&&... yuke)
	{
		audioManagerPtr->playSoundShakeRow(std::forward<Ts>(yuke)...);
	}
}