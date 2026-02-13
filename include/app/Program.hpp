#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <utility>
#include <memory>

#include "helper/splitToInteger.hpp"

#include "Types.hpp"

#include "managers/ScreenManager.hpp"

class Program
{
public:
	void run();

	explicit Program() = default;
	Program(const Program& other) = delete;
	Program& operator=(const Program& other) = delete;
	Program(Program&& other) = delete;
	Program& operator=(Program&& other) = delete;

private:
	std::unique_ptr<ScreenManager> p_screenManager;
};