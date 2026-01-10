#include "screen/TestScreen.hpp"
#include "app/globals.hpp"
#include <SFML/Graphics.hpp>

void TestScreen::update()
{

}

void TestScreen::draw()
{
	const sf::Font& font = Managers::fontManagerPtr->get("VCR_OSD_MONO");
	sf::Text allOKText(font, "SFML all OK!", 50);

	p_window->clear();
	p_window->draw(allOKText);
	p_window->display();
}