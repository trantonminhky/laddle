#pragma once
#include <string>
#include <SFML/Audio.hpp>

enum class Music
{
	MAIN
};

enum class Sound
{

};

class AudioManager
{
public:
	explicit AudioManager() = default;
	~AudioManager() = default;

	void load(const Sound& key, const std::string& path);
	void init();

	const sf::Sound& get(const Sound& sound) const;

private:
	std::unordered_map<Sound, sf::Sound> p_sounds;
	sf::Music music;
};