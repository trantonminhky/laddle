#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class FontManager
{
public:
	static FontManager& getInstance()
	{
		static FontManager instance;
		return instance;
	}

	void load(const std::string& key, const std::string& path);
	const sf::Font& get(const std::string& name) const;

private:
	FontManager() = default;
	~FontManager() = default;
	std::unordered_map<std::string, sf::Font> fonts;
};