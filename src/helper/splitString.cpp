#include "helper/splitString.hpp"
#include <sstream>

std::vector<std::string> splitString(const std::string& input, const char& delim)
{
	std::vector<std::string> tokens;
	if (!input.size()) return tokens;
	std::stringstream tokenStream("");

	for (const char& c : input)
	{
		if (c == delim)
		{
			auto token = tokenStream.str();
			tokens.push_back(token);
			tokenStream.str("");
			tokenStream.clear();
		}
		else
		{
			tokenStream << c;
		}
	}
	tokens.push_back(tokenStream.str());
	return tokens;
}