#pragma once
#include "Types.hpp"
#include <vector>
#include <string>

std::vector<int> solve(const std::vector<AdjacencyListEntry>& adjList, const std::vector<std::string>& wordList, const std::string& src, const std::string& dest);