#pragma once
#include <stack>

#include "screens/BaseScreen.hpp"

#include "ui/Row.hpp"

class PlayScreen : public BaseScreen
{
public:
	explicit PlayScreen() : BaseScreen()
	{
		Row initialRow;
		initialRow.setPosition(300.0f, 300.0f);
	}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

	~PlayScreen() = default;

private:
	std::stack<Row> p_rowStack;
	bool p_ignoreFirstFrame = true;
};