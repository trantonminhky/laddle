#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "helper/swag_assert.hpp"

// Discrete slider showing one value at a time
class Spinner : public sf::Transformable, public sf::Drawable
{
public:
	explicit Spinner(std::vector<std::string> options, const int& width, const int& initialValue = 0) : p_options(options), p_width(width), p_iterator(initialValue)
	{
		swag_assert(options.size() != 0);
		swag_assert(initialValue >= 0 && initialValue < static_cast<int>(options.size()));
	};

	explicit Spinner(const int& start, const int& endPlusOne, const int& width, const int& initialValue = 0) : p_options(), p_width(width), p_iterator(initialValue)
	{
		p_options.reserve(endPlusOne - start);
		for (auto i = start; i < endPlusOne; i++)
		{
			p_options.push_back(std::to_string(i));
		}
		
		swag_assert(endPlusOne - start > 0);
		swag_assert(initialValue >= 0 && initialValue < endPlusOne - start);
	}

	std::string getCurrentValue() const;

	void goNext();
	void goPrevious();

	void setLoop(const bool& loop = true);
	void setSize(const int& size);

	void draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const override;

protected:
	std::vector<std::string> p_options;
	int p_width;
	int p_iterator = 0;

	bool p_loop = false;
	int p_size = 10;
};