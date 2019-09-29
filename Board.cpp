#include "Board.h"



void Board::advanceSequentially()
{	
	vector<vector<int>> newState = this->gamestate;

	int x = this->dimensions[0];
	int y = this->dimensions[1];

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			int sum = this->getLocalSum(i, j);
			int currentValue = this->gamestate[i][j];

			if (currentValue == 0 && sum == 3) {
				newState[i][j] = 1;
			}
			else if (currentValue == 1 && (sum >= 4 || sum <= 1)) {
				newState[i][j] = 0;
			}
		}
	}

	this->setGamestate(newState);
}

int Board::getLocalSum(int i, int j)
{
	int sum = 0;

	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!(a == 0 && b == 0)) {
				int indexA = this->mod((i + a), (this->dimensions[1]));
				int indexB = this->mod((j + b), (this->dimensions[0]));

				sum += this->gamestate[indexA][indexB];
			}
		}
	}

	return sum;
}

int Board::mod(int a, int b)
{
	return (a % b + b) % b;
}

Board::Board()
{
}

Board::~Board()
{
}

void Board::setGamestate(vector<vector<int>> state)
{
	this->gamestate = state;
}

void Board::setDimensions(vector<int> dimensions)
{
	this->dimensions = dimensions;
}

void Board::advanceGenerationsBy(int count)
{
	for (int i = 0; i < count; i++) {
		this->advanceSequentially();
	}
}

std::string Board::toString()
{
	string result = "";

	for (int i = 0; i < this->dimensions[1]; i++) {
		for (int j = 0; j < this->dimensions[0]; j++) {
			result += this->gamestate[i][j];
		}

		result += "\n";
	}

	return result;
}
