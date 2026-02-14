#pragma once
#include <array>
#include <SFML/Graphics.hpp>

constexpr auto GAME_ACTIONS_COUNT = 9;

enum GameAction
{
	MAIN_MENU_MOVE_UP,
	MAIN_MENU_MOVE_DOWN,
	MAIN_MENU_SELECT,

	NOT_IMPLEMENTED_EXIT,

	PLAY_MOVE_PREVIOUS_ROW,
	PLAY_MOVE_NEXT_ROW,
	PLAY_BACKSPACE,
	PLAY_ENTER,
	PLAY_EXIT
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
	std::array<bool, GAME_ACTIONS_COUNT> p_actionStates;
};