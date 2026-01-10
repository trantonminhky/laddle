#pragma once
#include "helper/splitToInteger.hpp"
#include "Types.hpp"
#include "screen/BaseScreen.hpp"
#include "screen/TestScreen.hpp"
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <utility>
#include <memory>

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

// ////////////////////////////////////
// GAME STATES
enum class GameState
{
	NONE,
	TEST
};

class Program
{
public:
	void run();

	Program(ProgramFlags flags);
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
	GameState currentState = GameState::NONE;
	std::unique_ptr<BaseScreen> screenPtr;

	// helper functions
	void p_loadFromTxt();
	void p_init();
};