#pragma once
#include <array>
#include <SFML/Graphics.hpp>

enum GameAction
{
	MAIN_MENU_MOVE_UP,
	MAIN_MENU_MOVE_DOWN,
	MAIN_MENU_SELECT,

	NOT_IMPLEMENTED_EXIT,

	INSTRUCTION_MOVE_NEXT_PAGE,
	INSTRUCTION_MOVE_PREVIOUS_PAGE,
	INSTRUCTION_EXIT,

	PLAY_MOVE_PREVIOUS_ROW,
	PLAY_MOVE_NEXT_ROW,
	PLAY_BACKSPACE,
	PLAY_ENTER,
	PLAY_EXIT,

	GAME_ACTIONS_COUNT_THIS_IS_NOT_A_VALID_GAME_ACTION_DO_NOT_ACTUALLY_USE_THIS_OR_NASAL_DEMON_WILL_COME_OUT_OF_YOUR_ASS
};

class ActionManager
{
public:
	explicit ActionManager() = default;
	~ActionManager() = default;
	
	void checkActions(const sf::Event& event);
	bool hasAction(const GameAction& action) const;
	void clearActions();

private:
	std::array<bool, GAME_ACTIONS_COUNT_THIS_IS_NOT_A_VALID_GAME_ACTION_DO_NOT_ACTUALLY_USE_THIS_OR_NASAL_DEMON_WILL_COME_OUT_OF_YOUR_ASS> p_actionStates;
};