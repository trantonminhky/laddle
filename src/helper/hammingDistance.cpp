#include <iostream>

#include "helper/hammingDistance.hpp"
#include "helper/swag_assert.hpp"

int hammingDistance(const std::string& src, const std::string& dest)
{
	swag_assert(src.size() == dest.size());

	auto dist = 0;

	for (auto i = 0; i < src.size(); i++)
	{
		if (src[i] != dest[i]) dist++;
	}
	return dist;
}