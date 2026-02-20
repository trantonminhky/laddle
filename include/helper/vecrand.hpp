#pragma once

#include <unordered_set>
#include <random>

// returns random element in vector
template <typename T>
T vecrand(const std::vector<T>& vec)
{
	std::random_device rdev;
	std::mt19937 rgen(rdev());
	std::uniform_int_distribution<int> idist(0, vec.size() - 1);
	return vec[idist(rgen)];
}