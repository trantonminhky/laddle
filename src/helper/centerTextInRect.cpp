#include "helper/centerTextInRect.hpp"

void centerTextInRect(sf::Text& text, const sf::RectangleShape& rect)
{
	auto lbounds = text.getLocalBounds();
	auto gbounds = rect.getGlobalBounds();

	text.setOrigin({
		lbounds.position.x + lbounds.size.x / 2.0f,
		lbounds.position.y + lbounds.size.y / 2.0f
	});
	text.setPosition({
		gbounds.position.x + gbounds.size.x / 2.0f,
		gbounds.position.y + gbounds.size.y / 2.0f
	});
}