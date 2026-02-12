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

// /////////////////////////////////////
// PROGRAM MODES
enum class Mode
{
	NONE,
	HELP,
	SOLVE,
	GAME
};

struct ProgramFlags
{
	Mode mode = Mode::NONE;
	std::string solveFlagSrc;
	std::string solveFlagDest;
};

class Program
{
public:
	void run();

	explicit Program(ProgramFlags flags);
	Program(const Program& other) = delete;
	Program& operator=(const Program& other) = delete;
	Program(Program&& other) = delete;
	Program& operator=(Program&& other) = delete;

private:
	// internal data
	std::vector<std::string> p_wordList;
	std::vector<AdjacencyListEntry> p_adjList;

	// current app mode
	ProgramFlags p_flags;

	// -g state
	std::unique_ptr<ScreenManager> p_screenManager;

	// helper functions
	void p_loadFromTxt();
	void p_init();
};