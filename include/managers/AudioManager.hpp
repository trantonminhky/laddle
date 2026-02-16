#pragma once
#include <string>
#include <SFML/Audio.hpp>

enum class Musics
{
	MAIN
};

enum class Sounds
{
	INPUT_LETTER,
	INPUT_ROW,
	BACKSPACE_LETTER,
	SHAKE_ROW
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

	void playSoundInputLetter();
	void playSoundInputRow();
	void playSoundBackspaceLetter();
	void playSoundShakeRow();


private:
	std::unordered_map<Sounds, Audio> p_audios;
	sf::Music p_music;
};