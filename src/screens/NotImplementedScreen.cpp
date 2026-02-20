#include "screens/NotImplementedScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

bool NotImplementedScreen::handleInput(const sf::Event& event)
{
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::NOT_IMPLEMENTED_EXIT))
	{
		ScreenManager::retreat();
		ResourceManager::playSoundSelectMenuOption();
		captured = true;
	}

	ResourceManager::clearActions();
	return captured;
}

void NotImplementedScreen::update()
{
	
}

void NotImplementedScreen::p_drawText(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text notImplementedText(font, "not implemented :(", 50);

	window.draw(notImplementedText);
}

void NotImplementedScreen::draw(sf::RenderTarget& window) const
{
	const sf::Font& font = ResourceManager::getFont(Font::VCR_OSD_MONO);
	p_drawText(window, font);
}