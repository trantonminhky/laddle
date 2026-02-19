#include "screens/SettingsScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "ui/Spinner.hpp"

SettingsScreen::SettingsScreen() : BaseScreen()
{
	auto p_musicSpinnerPtr = std::make_unique<Spinner>(0, 101, 10, ResourceManager::getMusicVolume());
	p_musicSpinnerPtr->setLoop();
	p_musicSpinnerPtr->setSize(50);
	p_musicSpinnerPtr->setPosition({500.0f, 200.0f});
	p_spinners[0] = std::move(p_musicSpinnerPtr);

	auto p_SFXSpinnerPtr = std::make_unique<Spinner>(0, 101, 10, ResourceManager::getSFXVolume());
	p_SFXSpinnerPtr->setLoop();
	p_SFXSpinnerPtr->setSize(50);
	p_SFXSpinnerPtr->setPosition({500.0f, 300.0f});
	p_spinners[1] = std::move(p_SFXSpinnerPtr);
}

bool SettingsScreen::handleInput(const sf::Event &event)
{
	bool captured = false;
	ResourceManager::checkActions(event);

	if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_UP))
	{
		p_selector = (p_selector + SPINNERS_COUNT - 1) % SPINNERS_COUNT;
		ResourceManager::playSoundMoveMenuOption();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_DOWN))
	{
		p_selector = (p_selector + 1) % SPINNERS_COUNT;
		ResourceManager::playSoundMoveMenuOption();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_LEFT))
	{
		p_spinners[p_selector]->goPrevious();
		ResourceManager::playSoundMoveMenuOption();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_MOVE_RIGHT))
	{
		p_spinners[p_selector]->goNext();
		ResourceManager::playSoundMoveMenuOption();
		captured = true;
	}
	else if (ResourceManager::hasAction(GameAction::SETTINGS_EXIT))
	{
		ResourceManager::setMusicVolume(std::stoi(p_spinners[0]->getCurrentValue()));
		ResourceManager::setSFXVolume(std::stoi(p_spinners[1]->getCurrentValue()));

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

	sf::Text musicVolumeText(font, "Music:", 50);
	musicVolumeText.setPosition({300.0f, 200.0f});
	sf::Text SFXVolumeText(font, "SFX:", 50);
	SFXVolumeText.setPosition({300.0f, 300.0f});

	sf::Text selectorText(font, ">", 50);
	auto selectorYPosition = p_selector * 100.0f + 200.0f;
	auto lbounds = selectorText.getLocalBounds();
	selectorText.setPosition({window.getSize().x / 4.0f - 2.0f * lbounds.size.x, selectorYPosition});

	for (const auto& spinner : p_spinners)
	{
		window.draw(*spinner);
	}
	window.draw(musicVolumeText);
	window.draw(SFXVolumeText);
	window.draw(selectorText);
}