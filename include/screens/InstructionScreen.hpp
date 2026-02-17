#pragma once
#include <stack>

#include "screens/BaseScreen.hpp"

struct InstructionPage
{
	const char* text;
	const int lineWidth;
	const int fontSize;
};

constexpr auto MAX_INSTRUCTION_PAGES = 3;

constexpr InstructionPage INSTRUCTION_PAGE_ABOUT = {
	"Laddle (a portmanteau of Ladder and Wordle) is a word game inheriting both functionalities from Word Ladder and Wordle. You are given a source word, and through hints you must ladder your way to the answer.",
	35,
	50
};

constexpr InstructionPage INSTRUCTION_PAGE_HINTS = {
	"Each of your guesses should only differ by one letter at a time. Upon confirming your row, the row tiles may either be highlighted green, yellow, or none at all. When highlighted green, it means the answer contains the letter in the tile and at the correct position. When highlighted yellow, it means the answer contains the letter in the tile, but not at that position. No highlight means that letter does not exist in the answer.",
	35,
	45
};

constexpr InstructionPage INSTRUCTION_PAGE_KEYBINDS = {
	"Arrow Up - Move up\nArrow Down - Move down\nEnter - Select\nBackspace - Delete",
	35,
	50
};

constexpr std::array<InstructionPage, MAX_INSTRUCTION_PAGES> INSTRUCTION_PAGES = { INSTRUCTION_PAGE_ABOUT, INSTRUCTION_PAGE_HINTS, INSTRUCTION_PAGE_KEYBINDS };

class InstructionScreen : public BaseScreen
{
public:
	explicit InstructionScreen() : BaseScreen() {}

	bool handleInput(const sf::Event& event) override;
	void update() override;
	void draw(sf::RenderTarget& window) const override;

	~InstructionScreen() = default;

private:
	int p_iterator = 0;

	void p_drawText(sf::RenderTarget& window, const sf::Font& font) const;
	void p_drawArrow(sf::RenderTarget& window, const sf::Font& font) const;
};