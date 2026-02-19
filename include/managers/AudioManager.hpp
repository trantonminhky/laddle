#pragma once
#include <string>
#include <SFML/Audio.hpp>

enum class Musics
{
	MAIN
};

enum class Sounds
{
	MOVE_MENU_OPTION,
	SELECT_MENU_OPTION,

	INPUT_LETTER,
	INPUT_ROW,
	BACKSPACE_LETTER,
	SHAKE_ROW,
	MOVE_ROW
};

struct Audio
{
	std::unique_ptr<sf::SoundBuffer> bufferPtr;
	sf::Sound sound;
};

class AudioManager
{
public:
	explicit AudioManager() = default;
	~AudioManager() = default;

	void loadAudio(const Sounds& key, const std::string& path);
	void init();

	sf::Sound& getSound(const Sounds& sound);

	int getSFXVolume() const;
	int getMusicVolume() const;
	void setSFXVolume(const int& volume);
	void setMusicVolume(const int& volume);

	void playSoundMoveMenuOption();
	void playSoundSelectMenuOption();

	void playSoundInputLetter();
	void playSoundInputRow();
	void playSoundBackspaceLetter();
	void playSoundShakeRow();
	void playSoundMoveRow();



private:
	std::unordered_map<Sounds, Audio> p_audios;
	sf::Music p_music;

	int p_SFXVolume = 20;
	int p_musicVolume = 40;
};