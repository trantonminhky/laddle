#include "app/Program.hpp"
#include <exception>
#include <iostream>

int main(int argc, char* argv[])
{
	ProgramFlags flags;
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		if (arg == "-h") flags.mode = Mode::HELP;
		else if (arg == "-g") flags.mode = Mode::GAME;
		else if (arg == "-s" && i + 2 < argc)
		{
			flags.mode = Mode::SOLVE;
			flags.solveFlagSrc = argv[i + 1];
			flags.solveFlagDest = argv[i + 2];
			i += 2;
		}
		else
		{
			throw std::invalid_argument("bad options");
		}
	}

	Program program(flags);
	program.run();

	return 0;
}