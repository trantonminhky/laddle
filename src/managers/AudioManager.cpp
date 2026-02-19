#include "managers/AudioManager.hpp"

#include "helper/swag_assert.hpp"

struct SoundTableEntry
{
	const Sounds key;
	const char* path;
};

struct MusicTableEntry
{
	const Musics key;
	const char* path;
};

constexpr SoundTableEntry SOUND_TABLE[] = {
	{ Sounds::MOVE_MENU_OPTION, "./assets/sounds/move_menu_option.wav" },
	{ Sounds::SELECT_MENU_OPTION, "./assets/sounds/select_menu_option.wav" },

	{ Sounds::INPUT_LETTER, "./assets/sounds/input_letter.wav" },
	{ Sounds::INPUT_ROW, "./assets/sounds/input_row.wav" },
	{ Sounds::BACKSPACE_LETTER, "./assets/sounds/backspace_letter.wav" },
	{ Sounds::SHAKE_ROW, "./assets/sounds/shake_row.wav" },
	{ Sounds::MOVE_ROW, "./assets/sounds/move_row.wav" }
};

void AudioManager::loadAudio(const Sounds& key, const std::string& path)
{
	auto bufferPtr = std::make_unique<sf::SoundBuffer>(path);
	sf::Sound sound(*bufferPtr);
	Audio audio = {std::move(bufferPtr), sound};
	p_audios.insert({key, std::move(audio)});
}

void AudioManager::init()
{
	for (const auto& entry : SOUND_TABLE)
	{
		loadAudio(entry.key, entry.path);
	}

	swag_assert(p_music.openFromFile("./assets/music/main.ogg"));
	p_music.setVolume(p_musicVolume);
	p_music.play();
	p_music.setLooping(true);
}

sf::Sound& AudioManager::getSound(const Sounds& sound)
{
	return p_audios.at(sound).sound;
}

int AudioManager::getSFXVolume() const
{
	return p_SFXVolume;
}

int AudioManager::getMusicVolume() const
{
	return p_musicVolume;
}

void AudioManager::setSFXVolume(const int& volume)
{
	p_SFXVolume = volume;
}

void AudioManager::setMusicVolume(const int& volume)
{
	p_musicVolume = volume;
	p_music.setVolume(volume);
}

void AudioManager::playSoundMoveMenuOption()
{
	sf::Sound& sound = getSound(Sounds::MOVE_MENU_OPTION);
	sound.setVolume(p_SFXVolume);
	sound.play();
}

void AudioManager::playSoundSelectMenuOption()
{
	sf::Sound& sound = getSound(Sounds::SELECT_MENU_OPTION);
	sound.setVolume(p_SFXVolume);
	sound.play();
}

void AudioManager::playSoundInputLetter()
{
	sf::Sound& sound = getSound(Sounds::INPUT_LETTER);
	sound.setVolume(p_SFXVolume);
	sound.play();
}

void AudioManager::playSoundInputRow()
{
	sf::Sound& sound = getSound(Sounds::INPUT_ROW);
	sound.setVolume(p_SFXVolume);
	sound.play();
}

void AudioManager::playSoundBackspaceLetter()
{
	sf::Sound& sound = getSound(Sounds::BACKSPACE_LETTER);
	sound.setVolume(p_SFXVolume);
	sound.play();
}

void AudioManager::playSoundShakeRow()
{
	sf::Sound& sound = getSound(Sounds::SHAKE_ROW);
	sound.setVolume(p_SFXVolume);
	sound.play();
}

void AudioManager::playSoundMoveRow()
{
	sf::Sound& sound = getSound(Sounds::MOVE_ROW);
	sound.setVolume(p_SFXVolume);
	sound.play();
}