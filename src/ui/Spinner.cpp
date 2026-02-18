#include "ui/Spinner.hpp"

#include "helper/swag_assert.hpp"

#include "managers/ResourceManager.hpp"

void Spinner::goNext()
{
	if (p_loop)
	{
		p_iterator = (p_iterator + 1) % p_options.size();
	}
	else
	{
		p_iterator = std::min<int>(p_options.size() - 1, p_iterator + 1);
	}
}

void Spinner::goPrevious()
{
	if (p_loop)
	{
		p_iterator = (p_iterator + p_options.size() - 1) % p_options.size();
	}
	else
	{
		p_iterator = std::max(0, p_iterator - 1);
	}
}

void Spinner::setLoop(const bool& loop)
{
	p_loop = loop;
}

void Spinner::setSize(const int& size)
{
	p_size = size;
}

void Spinner::draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const
{
	auto currentOption = p_options[p_iterator];
	swag_assert(currentOption.size() < p_width - 2);
	
	const sf::Font& font = ResourceManager::getFont(Font::VCR_OSD_MONO);

	int padLeftSize = (p_width - currentOption.size()) / 2;
	int padRightSize = p_width - currentOption.size() - padLeftSize;
	std::string padLeft(" ", padLeftSize);
	std::string padRight(" ", padRightSize);

	sf::Text spinner(font, "[" + padLeft + currentOption + padRight + "]", p_size);
	target.draw(spinner);
}