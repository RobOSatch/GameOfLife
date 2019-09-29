#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include "Board.h"

using namespace std;

class FileManager
{
public:
	FileManager();
	~FileManager();

	static Board* importFile(string filename);
	static void exportFile(const Board board, string filename);
};

