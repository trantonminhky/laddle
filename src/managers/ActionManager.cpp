#include "managers/ActionManager.hpp"

void ActionManager::checkActions(const sf::Event& event)
{
	auto keyPressedEvent = event.getIf<sf::Event::KeyPressed>();

	/*
		#######################################
		############# MAIN MENU ###############
		#######################################
	*/
	if (keyPressedEvent)
	{
		auto scancode = keyPressedEvent->scancode;
		p_actionStates[GameAction::MAIN_MENU_MOVE_UP] = (
			scancode == sf::Keyboard::Scan::Up ||
			scancode == sf::Keyboard::Scan::W
		);
		p_actionStates[GameAction::MAIN_MENU_MOVE_DOWN] = (
			scancode == sf::Keyboard::Scan::Down ||
			scancode == sf::Keyboard::Scan::S
		);
		p_actionStates[GameAction::MAIN_MENU_SELECT] = (
			scancode == sf::Keyboard::Scan::Enter ||
			scancode == sf::Keyboard::Scan::Z
		);
	}

	/*
		#######################################
		########### NOT IMPLEMENTED ###########
		#######################################
	*/
	if (keyPressedEvent)
	{
		auto scancode = keyPressedEvent->scancode;
		p_actionStates[GameAction::NOT_IMPLEMENTED_EXIT] = (
			scancode == sf::Keyboard::Scan::Backspace ||
			scancode == sf::Keyboard::Scan::X ||
			scancode == sf::Keyboard::Scan::Escape
		);
	}

	/*
		########################################
		################# TEST #################
		########################################
	*/
	if (keyPressedEvent)
	{
		auto scancode = keyPressedEvent->scancode;
		p_actionStates[GameAction::TEST_EXIT] = (
			scancode == sf::Keyboard::Scan::Escape
		);
		p_actionStates[GameAction::TEST_BACKSPACE] = (
			scancode == sf::Keyboard::Scan::Backspace
		);
		p_actionStates[GameAction::TEST_ENTER] = (
			scancode == sf::Keyboard::Scan::Enter
		);
	}

	/*
		########################################
		################# PLAY #################
		########################################
	*/
	if (keyPressedEvent)
	{
		auto scancode = keyPressedEvent->scancode;
		p_actionStates[GameAction::PLAY_MOVE_PREVIOUS_ROW] = (
			scancode == sf::Keyboard::Scan::Up
		);
		p_actionStates[GameAction::PLAY_MOVE_NEXT_ROW] = (
			scancode == sf::Keyboard::Scan::Down
		);
		p_actionStates[GameAction::PLAY_EXIT] = (
			scancode == sf::Keyboard::Scan::Escape
		);
		p_actionStates[GameAction::PLAY_BACKSPACE] = (
			scancode == sf::Keyboard::Scan::Backspace
		);
		p_actionStates[GameAction::PLAY_ENTER] = (
			scancode == sf::Keyboard::Scan::Enter
		);
	}
}

bool ActionManager::hasAction(const GameAction& action) const
{
	return p_actionStates[action];
}

void ActionManager::clearActions()
{
	for (int i = 0; i < GAME_ACTIONS_COUNT; i++)
	{
		p_actionStates[i] = false;
	}
}