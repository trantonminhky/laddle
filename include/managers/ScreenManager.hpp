#pragma once
#include <stack>
#include <memory>

#include "screens/BaseScreen.hpp"
#include "screens/MainMenuScreen.hpp"
#include "screens/NotImplementedScreen.hpp"
#include "screens/TestScreen.hpp"
#include "screens/PlayScreen.hpp"

class ScreenManager
{
public:
	explicit ScreenManager() = default;
	~ScreenManager() = default;

	void init();

	static void advance(GameState nextState);
	static void retreat();

	bool handleInput(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& window);

	GameState getCurrentState() const;

	bool shouldExit() const;

private:
	static std::stack<GameState> p_stateStack;
	static std::stack<std::unique_ptr<BaseScreen>> p_screenStack;
};