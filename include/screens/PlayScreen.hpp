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
	void draw(sf::RenderTarget& window) const override;

	~PlayScreen() = default;

private:
	std::vector<Row> p_rowStack;
	int p_iterator = -1;
	bool p_detachedHead = false;

	std::string p_source;
	std::string p_answer;
	std::string p_message = "Go on...";

	bool p_ignoreFirstFrame = true;

	void p_generateSourceAndAnswer();
	void p_initFirstGuess();

	void p_pushRow();
	void p_popRow();

	void p_drawMessage(sf::RenderTarget& window, const sf::Font& font) const;
	void p_drawRows(sf::RenderTarget& window, int start, int end) const;
	void p_drawEllipses(sf::RenderTarget& window, const sf::Font& font, int start, int end) const;
};