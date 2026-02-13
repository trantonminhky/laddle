#include "managers/ScreenManager.hpp"

#include "helper/swag_assert.hpp"

std::stack<GameState> ScreenManager::p_stateStack;
std::stack<std::unique_ptr<BaseScreen>> ScreenManager::p_screenStack;

void ScreenManager::init()
{
	p_stateStack.push(GameState::MAIN_MENU);
	p_screenStack.push(std::make_unique<MainMenuScreen>());
}

void ScreenManager::advance(GameState nextState)
{
	switch (nextState)
	{
		case GameState::MAIN_MENU:
		{
			p_stateStack.push(GameState::MAIN_MENU);
			p_screenStack.push(std::make_unique<MainMenuScreen>());
			break;
		}

		case GameState::TEST:
		{
			p_stateStack.push(GameState::TEST);
			p_screenStack.push(std::make_unique<TestScreen>());
			break;
		}

		case GameState::PLAY:
		{
			p_stateStack.push(GameState::TEST);
			p_screenStack.push(std::make_unique<PlayScreen>());
			break;
		}

		default:
		{
			p_stateStack.push(GameState::NOT_IMPLEMENTED);
			p_screenStack.push(std::make_unique<NotImplementedScreen>());
			break;
		}
	}
}

void ScreenManager::retreat()
{
	p_screenStack.pop();
}

bool ScreenManager::handleInput(const sf::Event& event)
{
	swag_assert(!p_screenStack.empty());
	return p_screenStack.top()->handleInput(event);
}

void ScreenManager::update()
{
	swag_assert(!p_screenStack.empty());
	p_screenStack.top()->update();
}

void ScreenManager::draw(sf::RenderTarget& window)
{
	swag_assert(!p_screenStack.empty());
	p_screenStack.top()->draw(window);
}

GameState ScreenManager::getCurrentState() const
{
	swag_assert(!p_stateStack.empty());
	return p_stateStack.top();
}

bool ScreenManager::shouldExit() const
{
	return p_screenStack.empty();
}