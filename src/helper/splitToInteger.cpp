#include "helper/splitToInteger.hpp"
#include <string>
#include <unordered_set>
#include <sstream>

// this is a bit different from regular string split, in that calling splitToInteger on "" would yield [] instead of [""]
std::unordered_set<int> splitToInteger(const std::string& input, const char& delim)
{
	std::unordered_set<int> tokens;
	if (!input.size()) return tokens;
	std::stringstream tokenStream("");

	for (const char& c : input)
	{
		if (c == delim)
		{
			int token = std::stoi(tokenStream.str());
			tokens.insert(token);
			tokenStream.str("");
			tokenStream.clear();
		}
		else
		{
			tokenStream << c;
		}
	}
	tokens.insert(std::stoi(tokenStream.str()));
	return tokens;
}