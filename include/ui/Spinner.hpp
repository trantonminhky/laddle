#pragma once
#include <SFML/Graphics.hpp>

// Discrete slider showing one value at a time
class Spinner : public sf::Transformable, public sf::Drawable
{
public:
	explicit Spinner(std::vector<std::string> options, const int& width) : p_options(options), p_width(width) {};

	void goNext();
	void goPrevious();

	void setLoop(const bool& loop = true);
	void setSize(const int& size);

	void draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const override;

private:
	int p_iterator = 0;
	std::vector<std::string> p_options;
	int p_width;

	bool p_loop = false;
	int p_size = 10;
};