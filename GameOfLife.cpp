// GameOfLife.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "FileManager.h"
#include "Timer.h"

using namespace std;

enum MODE {
	seq
};

int main(int argc, char* argv[])
{
	string inputfile;
	string outputfile;
	int generations = 0;
	bool shouldMeasure = false;
	MODE mode;

	// Perform argument stuff
	for (int i = 0; i < argc; i++) {
		string currentArgument = argv[i];

		if (currentArgument == "--load") {
			inputfile = argv[i + 1];
		}

		if (currentArgument == "--generations") {
			generations = stoi(argv[i + 1]);
		}

		if (currentArgument == "--save") {
			outputfile = argv[i + 1];
		}

		if (currentArgument == "--measure") {
			shouldMeasure = true;
		}

		if (currentArgument == "--mode") {
			if (argv[i + 1] == "seq") {
				mode = seq;
			}
		}
	}
	
	// Read input from file and store in memory
	Timer::start();
	Board* board = FileManager::importFile(inputfile);
	Timer::stop();

	// Compute generations
	Timer::start();
	board->advanceGenerationsBy(generations);
	Timer::stop();

	// Export new gamestate to file
	Timer::start();
	FileManager::exportFile(*board, outputfile);
	Timer::stop();

	return 0;
}