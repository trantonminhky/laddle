#pragma once
#include <string>
#include <SFML/Audio.hpp>

enum class Music
{
	MAIN
};

enum class Sound
{
	INPUT_LETTER
};

class AudioManager
{
public:
	explicit AudioManager() = default;
	~AudioManager() = default;

	void loadSoundBuffer(const Sound& key, const std::string& path);
	void init();

	const sf::SoundBuffer& getSoundBuffer(const Sound& sound) const;
	void playSoundInputLetter() const;


private:
	std::unordered_map<Sound, sf::SoundBuffer> p_soundBuffers;
	sf::Music music;
};