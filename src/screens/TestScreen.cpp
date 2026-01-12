#include <iostream>
#include "screens/TestScreen.hpp"
#include "contexts/GameContext.hpp"
#include <SFML/Graphics.hpp>

void TestScreen::handleInput(const sf::Event& event)
{
	if (event.is<sf::Event::TextEntered>())
	{
		char letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (p_row.isFull())
			{
				p_row.reset();
				std::cout << "RESET\n";
			}
			else p_row.appendLetter(letter);
		}
	}
}

void TestScreen::update()
{

}

void TestScreen::draw()
{
	const sf::Font& font = GameContext::getFont("VCR_OSD_MONO");
	sf::Text allOKText(font, "SFML all OK!", 50);

	p_window->clear();
	p_window->draw(allOKText);
	
	sf::Vector2f currentTilePosition = p_row.getPosition();
	for (int i = 0; i < WORD_LENGTH; i++)
	{
		sf::RectangleShape tileRect({80.0f, 80.f});
		tileRect.setPosition(currentTilePosition);
		char tileLetter = p_row.getTileAtIndex(i).getLetter();
		sf::Text tileLetterText(font, tileLetter, 50);
		tileLetterText.setFillColor(sf::Color::Black);
		tileLetterText.setPosition(currentTilePosition);

		p_window->draw(tileRect);
		p_window->draw(tileLetterText);

		currentTilePosition.x += 90;
	}

	p_window->display();
}