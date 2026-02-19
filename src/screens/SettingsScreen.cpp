#include "screens/SettingsScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "ui/Spinner.hpp"

SettingsScreen::SettingsScreen() : BaseScreen()
{
	p_musicSpinnerPtr = std::make_unique<Spinner>(0, 101, 10, ResourceManager::getMusicVolume());
	p_musicSpinnerPtr->setLoop();
	p_musicSpinnerPtr->setSize(50);
	p_musicSpinnerPtr->setPosition({500.0f, 200.0f});


	p_SFXSpinnerPtr = std::make_unique<Spinner>(0, 101, 10, ResourceManager::getSFXVolume());
	p_SFXSpinnerPtr->setLoop();
	p_SFXSpinnerPtr->setSize(50);
	p_SFXSpinnerPtr->setPosition({500.0f, 300.0f});
}

bool SettingsScreen::handleInput(const sf::Event &event)
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
		p_musicSpinnerPtr->goPrevious();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_RIGHT))
	{
		p_musicSpinnerPtr->goNext();
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

void SettingsScreen::draw(sf::RenderTarget &window) const
{
	const sf::Font &font = ResourceManager::getFont(Font::VCR_OSD_MONO);

	window.draw(*p_musicSpinnerPtr);
	window.draw(*p_SFXSpinnerPtr);
}