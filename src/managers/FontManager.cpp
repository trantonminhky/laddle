#include <managers/FontManager.hpp>

struct FontTableEntry
{
	const Font key;
	const char* path;
};

constexpr FontTableEntry FONT_TABLE[] = {
	{Font::VCR_OSD_MONO, "assets/fonts/VCR_OSD_MONO.ttf"}
};

void FontManager::load(const Font& key, const std::string& path)
{
	sf::Font font(path);
	p_fonts.insert({key, font});
}

void FontManager::init()
{
	for (auto entry : FONT_TABLE)
	{
		load(entry.key, entry.path);
	}
}

const sf::Font& FontManager::get(const Font& font) const
{
	return p_fonts.at(font);
}