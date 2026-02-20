#include "screens/SettingsScreen.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/ScreenManager.hpp"

#include "ui/Spinner.hpp"

constexpr auto VOLUME_SPINNER_START = 0;
constexpr auto VOLUME_SPINNER_END_PLUS_1 = 101;
constexpr auto VOLUME_SPINNER_WIDTH = 10;
constexpr auto VOLUME_SPINNER_SIZE = 60;
constexpr sf::Vector2f MUSIC_VOLUME_SPINNER_POSITION = {500.0f, 200.0f};
constexpr sf::Vector2f SFX_VOLUME_SPINNER_POSITION = {500.0f, 280.0f};

constexpr auto SETTINGS_OPTIONS_TEXT_FONT_SIZE = 60;
constexpr auto SETTINGS_OPTIONS_INDENT = 4.0f;
constexpr auto SETTINGS_OPTIONS_FIRST_OPTION_Y_POSITION = 200.0f;
constexpr auto SETTINGS_OPTIONS_VERTICAL_SPACING = 80.0f;

constexpr auto MUSIC_VOLUME_TEXT_Y_POSITION = SETTINGS_OPTIONS_FIRST_OPTION_Y_POSITION + SETTINGS_OPTIONS_VERTICAL_SPACING * 0;
constexpr auto SFX_VOLUME_TEXT_Y_POSITION = SETTINGS_OPTIONS_FIRST_OPTION_Y_POSITION + SETTINGS_OPTIONS_VERTICAL_SPACING * 1;

constexpr auto SELECTOR_TEXT_FONT_SIZE = 60;
constexpr auto SELECTOR_HORIZONTAL_SPACING = 2.0f;

SettingsScreen::SettingsScreen() : BaseScreen()
{
	auto p_musicSpinnerPtr = std::make_unique<Spinner>(VOLUME_SPINNER_START, VOLUME_SPINNER_END_PLUS_1, VOLUME_SPINNER_WIDTH, ResourceManager::getMusicVolume());
	p_musicSpinnerPtr->setLoop();
	p_musicSpinnerPtr->setSize(VOLUME_SPINNER_SIZE);
	p_musicSpinnerPtr->setPosition(MUSIC_VOLUME_SPINNER_POSITION);
	p_spinners[0] = std::move(p_musicSpinnerPtr);

	auto p_SFXSpinnerPtr = std::make_unique<Spinner>(VOLUME_SPINNER_START, VOLUME_SPINNER_END_PLUS_1, VOLUME_SPINNER_WIDTH, ResourceManager::getSFXVolume());
	p_SFXSpinnerPtr->setLoop();
	p_SFXSpinnerPtr->setSize(VOLUME_SPINNER_SIZE);
	p_SFXSpinnerPtr->setPosition(SFX_VOLUME_SPINNER_POSITION);
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

void SettingsScreen::p_drawTexts(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text musicVolumeText(font, "Music:", SETTINGS_OPTIONS_TEXT_FONT_SIZE);
	sf::Text SFXVolumeText(font, "SFX:", SETTINGS_OPTIONS_TEXT_FONT_SIZE);
	musicVolumeText.setPosition({window.getSize().x / SETTINGS_OPTIONS_INDENT, MUSIC_VOLUME_TEXT_Y_POSITION});
	SFXVolumeText.setPosition({window.getSize().x / SETTINGS_OPTIONS_INDENT, SFX_VOLUME_TEXT_Y_POSITION});

	window.draw(musicVolumeText);
	window.draw(SFXVolumeText);
}

void SettingsScreen::p_drawSelector(sf::RenderTarget& window, const sf::Font& font) const
{
	sf::Text selectorText(font, ">", SELECTOR_TEXT_FONT_SIZE);
	auto selectorYPosition = p_selector * SETTINGS_OPTIONS_VERTICAL_SPACING + SETTINGS_OPTIONS_FIRST_OPTION_Y_POSITION;
	auto lbounds = selectorText.getLocalBounds();
	selectorText.setPosition({window.getSize().x / SETTINGS_OPTIONS_INDENT - SELECTOR_HORIZONTAL_SPACING * lbounds.size.x, selectorYPosition});

	window.draw(selectorText);
}

void SettingsScreen::p_drawSpinners(sf::RenderTarget& window) const
{
	for (const auto& spinner : p_spinners)
	{
		window.draw(*spinner);
	}
}

void SettingsScreen::draw(sf::RenderTarget &window) const
{
	const sf::Font& font = ResourceManager::getFont(Font::VCR_OSD_MONO);
	
	p_drawTexts(window, font);
	p_drawSelector(window, font);
	p_drawSpinners(window);
}