#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board
{
private:
	void advance();
	int getLocalSum(int i, int j);
	int mod(int a, int b);

public:
	Board();
	~Board();

	vector<int> dimensions;
	vector<vector<int>> gamestate;

	void setGamestate(vector<vector<int>> state);
	void setDimensions(vector<int> dimensions);

	void advanceGenerationsBy(int count);

	std::string toString();
};

