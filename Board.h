#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <CL/cl.hpp>

using namespace std;

class Board
{
private:
	// Variables
	std::vector<cl::Platform> platforms;
	std::vector<cl::Device> devices;
	cl::Platform platform;
	cl::Device device;
	cl::Program program;
	cl::Kernel kernel;
	cl::Buffer gamestateBuffer;
	cl::Buffer newstateBuffer;
	cl::Event event;
	cl::CommandQueue queue;
	const std::string KERNEL_FILE = "../../gameOfLife.cl";

	void advanceSequentially();
	void advanceOpenMP();
	void advanceOpenCL();

public:
	enum PARALLEL_MODE {
		eSequential,
		eOpenMP,
		eOpenCL
	};

	Board();
	~Board();
	int mod(int a, int b);
	vector<int> dimensions;
	vector<vector<int>> gamestate;
	vector<cl_int> data;

	void setupOpenCL(const int& width, const int height, unsigned __int64 deviceType, int platformId, int deviceID);

	void setGamestate(vector<vector<int>> state);
	void setDimensions(vector<int> dimensions);

	void advanceGenerationsBy(int count, PARALLEL_MODE mode);

	std::string toString();
};

