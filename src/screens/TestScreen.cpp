#include <iostream>
#include "screens/TestScreen.hpp"
#include "contexts/GameContext.hpp"
#include "helper/centerTextInRect.hpp"
#include <SFML/Graphics.hpp>

void TestScreen::handleInput(const sf::Event& event)
{
	if (event.is<sf::Event::KeyPressed>())
	{
		auto scancode = event.getIf<sf::Event::KeyPressed>()->scancode;
		if (scancode == sf::Keyboard::Scan::Backspace)
		{
			p_row.popLetter();
		}
		else if (scancode == sf::Keyboard::Scan::Enter)
		{
			if (p_row.isFull()) 
			{
				std::cout << p_row.getWord() << '\n';
				p_row.reset();
			}
			else
			{
				std::cout << "shake" << '\n';
				p_row.shake();
			}
		}
	}
	else if (event.is<sf::Event::TextEntered>())
	{
		auto letter = event.getIf<sf::Event::TextEntered>()->unicode;
		if (letter >= 'a' && letter <= 'z')
		{
			if (!p_row.isFull())
			{
				p_row.pushLetter(letter);
			}
		}
	}
}

void TestScreen::update()
{
	p_row.update();
}

void TestScreen::draw()
{
	const sf::Font& font = GameContext::getFont("VCR_OSD_MONO");
	sf::Text allOKText(font, "SFML all OK!", 50);

	p_window->clear();
	p_window->draw(allOKText);
	p_window->draw(p_row);
	p_window->display();
}