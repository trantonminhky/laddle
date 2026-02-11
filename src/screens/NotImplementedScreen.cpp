#include "screens/NotImplementedScreen.hpp"

#include "contexts/GameContext.hpp"

bool NotImplementedScreen::handleInput(const sf::Event& event)
{
	return true;
}

void NotImplementedScreen::update()
{

}

void NotImplementedScreen::draw(sf::RenderTarget& window)
{
	const sf::Font& font = GameContext::getFont("VCR_OSD_MONO");
	sf::Text notImplementedText(font, "not implemented :(", 50);

	window.draw(notImplementedText);
}