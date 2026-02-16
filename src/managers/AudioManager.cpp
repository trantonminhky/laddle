#include "managers/AudioManager.hpp"

#include "helper/swag_assert.hpp"

struct SoundTableEntry
{
	const Sound key;
	const char* path;
};

struct MusicTableEntry
{
	const Music key;
	const char* path;
};

constexpr SoundTableEntry SOUND_TABLE[] = {
	{ Sound::INPUT_LETTER, "./assets/sounds/input_letter.wav" }
};

void AudioManager::loadSoundBuffer(const Sound& key, const std::string& path)
{
	sf::SoundBuffer soundBuffer(path);
	p_soundBuffers.insert({key, soundBuffer});
}

void AudioManager::init()
{
	for (const auto& entry : SOUND_TABLE)
	{
		loadSoundBuffer(entry.key, entry.path);
	}

	swag_assert(music.openFromFile("./assets/music/main.ogg"));
	music.play();
	music.setLooping(true);
}

const sf::SoundBuffer& AudioManager::getSoundBuffer(const Sound& sound) const
{
	return p_soundBuffers.at(sound);
}

void AudioManager::playSoundInputLetter() const
{
	sf::Sound sound(p_soundBuffers.at(Sound::INPUT_LETTER));
	sound.play();
}