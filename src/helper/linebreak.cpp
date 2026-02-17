#include "helper/linebreak.hpp"
#include "helper/splitString.hpp"

#include <iostream>

std::string linebreak(const std::string& input, const int& maxSpace)
{
	auto tokens = splitString(input, ' ');
	auto spaceLeft = maxSpace;
	std::string result;

	for (const auto& token : tokens)
	{
		if (token.size() + 1 > spaceLeft)
		{
			result += '\n';
			spaceLeft = maxSpace - token.size();
		}
		else
		{
			spaceLeft = spaceLeft - (token.size() + 1);
		}
		result += token + ' ';
	}
	return result;
}