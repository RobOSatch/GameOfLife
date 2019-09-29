#include "FileManager.h"


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

Board* FileManager::importFile(string filename)
{
	std::ifstream myfile;
	myfile.open("InputFiles/" + filename + ".gol");
	std::string a;

	std::getline(myfile, a);

	std::vector<int> dimensions;

	std::string token;
	std::istringstream tokenStream(a);
	while (std::getline(tokenStream, token, ',')) {
		dimensions.push_back(std::stoi(token));
	}

	vector<vector<int>> board;
	int j = 0;
	while (std::getline(myfile, a)) {
		board.push_back(std::vector<int>());
		for (int i = 0; i < a.size(); i++) {
			board[j].push_back(a[i] == 'x' ? 1 : 0);
		}

		j++;
	}

	myfile.close();

	Board* gameBoard = new Board();
	gameBoard->setDimensions(dimensions);
	gameBoard->setGamestate(board);

	return gameBoard;
}

void FileManager::exportFile(const Board board, string filename)
{
	int x = board.dimensions[0];
	int y = board.dimensions[1];

	ofstream myfile;
	myfile.open("OutputFiles/" + filename + ".gol");
	myfile << x << "," << y << endl;

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (board.gamestate[i][j] == 0) {
				myfile << ".";
			}
			else {
				myfile << "x";
			}
		}

		myfile << endl;
	}

	myfile.close();
}
