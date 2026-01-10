#include "app/solve.hpp"
#include "algo/dijkstra.hpp"
#include "algo/binarySearch.hpp"
#include <iostream>
#include <algorithm>

std::vector<int> solve(const std::vector<AdjacencyListEntry>& adjList, const std::vector<std::string>& wordList, const std::string& src, const std::string& dest)
{
	auto srcIteratorOptional = binarySearch<std::vector<std::string>::const_iterator>(wordList.cbegin(), wordList.cend(), src);
	auto destIteratorOptional = binarySearch<std::vector<std::string>::const_iterator>(wordList.cbegin(), wordList.cend(), dest);

	if (!srcIteratorOptional || !destIteratorOptional)
	{
		std::cout << "Invalid words input";
		return {};
	}

	int srcIndex = *srcIteratorOptional - wordList.cbegin();
	int destIndex = *destIteratorOptional - wordList.cbegin();
	auto result = dijkstra(adjList, srcIndex, destIndex);
	return result;
}