#include "screens/SettingsScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

bool SettingsScreen::handleInput(const sf::Event& event)
{
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_UP))
	{
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_DOWN))
	{
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_LEFT))
	{
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_RIGHT))
	{
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_EXIT))
	{
		ScreenManager::retreat();
		captured = true;
	}

	ResourceManager::clearActions();
	return captured;
}

void SettingsScreen::update()
{

}

void SettingsScreen::draw(sf::RenderTarget& window) const
{
	const sf::Font& font = ResourceManager::getFont(Font::VCR_OSD_MONO);
	
}