#include "managers/ActionManager.hpp"

void ActionManager::checkActions(const sf::Event& event)
{
	auto keyPressedEvent = event.getIf<sf::Event::KeyPressed>();
	auto textEnteredEvent = event.getIf<sf::Event::TextEntered>();

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
		) ? true : false;
		p_actionStates[GameAction::MAIN_MENU_MOVE_DOWN] = (
			scancode == sf::Keyboard::Scan::Down ||
			scancode == sf::Keyboard::Scan::S
		) ? true : false;
		p_actionStates[GameAction::MAIN_MENU_SELECT] = (
			scancode == sf::Keyboard::Scan::Enter ||
			scancode == sf::Keyboard::Scan::Z
		) ? true : false;
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
			scancode == sf::Keyboard::Scan::X
		) ? true : false;
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
		) ? true : false;
		p_actionStates[GameAction::TEST_BACKSPACE] = (
			scancode == sf::Keyboard::Scan::Backspace
		) ? true : false;
		p_actionStates[GameAction::TEST_ENTER] = (
			scancode == sf::Keyboard::Scan::Enter
		) ? true : false;
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