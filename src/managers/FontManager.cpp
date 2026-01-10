#include <managers/FontManager.hpp>

void FontManager::load(const std::string& key, const std::string& path)
{
	sf::Font font(path);
	fonts.insert({key, font});
}

const sf::Font& FontManager::get(const std::string& name) const
{
	return fonts.at(name);
}