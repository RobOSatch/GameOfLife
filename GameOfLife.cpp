// GameOfLife.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <numeric>
#include <algorithm>

#include <omp.h>

#include "FileManager.h"
#include "Timer.h"
#include "Board.h"

using namespace std;

int main(int argc, char* argv[])
{
	string inputfile;
	string outputfile;
	int generations = 0;
	bool shouldMeasure = false;
	int threadCount = 32;
	int device = 1;
	int platformID = 0;
	int deviceID = 0;
	Board::PARALLEL_MODE mode;

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
			string argValue = argv[i + 1];
			if (argValue == "seq") {
				mode = Board::eSequential;
			}
			else if (argValue == "omp") {
				mode = Board::eOpenMP;
			}
			else if (argValue == "ocl") {
				mode = Board::eOpenCL;
			}
		}
		
		if (mode == Board::eOpenMP) {
			if (currentArgument == "--threads") {
				threadCount = stoi(argv[i + 1]);
			}
		}

		if (mode == Board::eOpenCL) {
			if (currentArgument == "--device") {
				string argValue = argv[i + 1];
				if (argValue == "cpu") device = 0;
				else if (argValue == "gpu") device = 1;
			}
			else if (currentArgument == "--platformId") {
				platformID = stoi(argv[i + 1]);
			}
			else if (currentArgument == "--deviceId") {
				deviceID = stoi(argv[i + 1]);
			}
		}
	}

	// Read input from file and store in memory
	if (shouldMeasure) Timer::start();
	Board* board = FileManager::importFile(inputfile);
	if (shouldMeasure) Timer::stop();

	vector<vector<int>> gamestate = board->gamestate;

	int x = board->dimensions[0];
	int y = board->dimensions[1];

	if (mode == Board::eOpenMP) omp_set_num_threads(32);
	else if (mode == Board::eOpenCL) board->setupOpenCL(x, y, device, platformID, deviceID);

	// Compute generations
	if (shouldMeasure) Timer::start();
	board->advanceGenerationsBy(generations, mode);
	if (shouldMeasure) Timer::stop();

	//board->setGamestate(gamestate);

	// Export new gamestate to file
	if (shouldMeasure) Timer::start();
	if (mode == Board::eOpenCL) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				board->gamestate[i][j] = board->data[i * x + j];
			}
		}
	}
	FileManager::exportFile(*board, outputfile);
	board = nullptr;
	if (shouldMeasure) Timer::stop();

	return 0;
}