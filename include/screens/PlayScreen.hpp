#pragma once
#include <stack>

#include "screens/BaseScreen.hpp"

#include "ui/Row.hpp"

#include "Types.hpp"

class PlayScreen : public BaseScreen
{
public:
	explicit PlayScreen();

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) override;

	~PlayScreen() = default;

private:
	std::vector<Row> p_rowStack;
	std::string p_answer;

	bool p_ignoreFirstFrame = true;
};