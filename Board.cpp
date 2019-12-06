#include "Board.h"
#include <omp.h>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
// opencltest.cpp : an example for using OpenCL with C++
// requirements: 
// - CUDA Toolkit 9.0 (sets the environment variable CUDA_PATH)
// - cl.hpp, the C++ bindings for OpenCL v 1.2
//
// author: Eugen Jiresch
//
#define __CL_ENABLE_EXCEPTIONS

// list of error codes from "CL/cl.h"
std::string cl_errorstring(cl_int err) {
	switch (err) {
	case CL_SUCCESS:                          return std::string("Success");
	case CL_DEVICE_NOT_FOUND:                 return std::string("Device not found");
	case CL_DEVICE_NOT_AVAILABLE:             return std::string("Device not available");
	case CL_COMPILER_NOT_AVAILABLE:           return std::string("Compiler not available");
	case CL_MEM_OBJECT_ALLOCATION_FAILURE:    return std::string("Memory object allocation failure");
	case CL_OUT_OF_RESOURCES:                 return std::string("Out of resources");
	case CL_OUT_OF_HOST_MEMORY:               return std::string("Out of host memory");
	case CL_PROFILING_INFO_NOT_AVAILABLE:     return std::string("Profiling information not available");
	case CL_MEM_COPY_OVERLAP:                 return std::string("Memory copy overlap");
	case CL_IMAGE_FORMAT_MISMATCH:            return std::string("Image format mismatch");
	case CL_IMAGE_FORMAT_NOT_SUPPORTED:       return std::string("Image format not supported");
	case CL_BUILD_PROGRAM_FAILURE:            return std::string("Program build failure");
	case CL_MAP_FAILURE:                      return std::string("Map failure");
	case CL_MISALIGNED_SUB_BUFFER_OFFSET:     return std::string("Misaligned sub buffer offset");
	case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST: return std::string("Exec status error for events in wait list");
	case CL_INVALID_VALUE:                    return std::string("Invalid value");
	case CL_INVALID_DEVICE_TYPE:              return std::string("Invalid device type");
	case CL_INVALID_PLATFORM:                 return std::string("Invalid platform");
	case CL_INVALID_DEVICE:                   return std::string("Invalid device");
	case CL_INVALID_CONTEXT:                  return std::string("Invalid context");
	case CL_INVALID_QUEUE_PROPERTIES:         return std::string("Invalid queue properties");
	case CL_INVALID_COMMAND_QUEUE:            return std::string("Invalid command queue");
	case CL_INVALID_HOST_PTR:                 return std::string("Invalid host pointer");
	case CL_INVALID_MEM_OBJECT:               return std::string("Invalid memory object");
	case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:  return std::string("Invalid image format descriptor");
	case CL_INVALID_IMAGE_SIZE:               return std::string("Invalid image size");
	case CL_INVALID_SAMPLER:                  return std::string("Invalid sampler");
	case CL_INVALID_BINARY:                   return std::string("Invalid binary");
	case CL_INVALID_BUILD_OPTIONS:            return std::string("Invalid build options");
	case CL_INVALID_PROGRAM:                  return std::string("Invalid program");
	case CL_INVALID_PROGRAM_EXECUTABLE:       return std::string("Invalid program executable");
	case CL_INVALID_KERNEL_NAME:              return std::string("Invalid kernel name");
	case CL_INVALID_KERNEL_DEFINITION:        return std::string("Invalid kernel definition");
	case CL_INVALID_KERNEL:                   return std::string("Invalid kernel");
	case CL_INVALID_ARG_INDEX:                return std::string("Invalid argument index");
	case CL_INVALID_ARG_VALUE:                return std::string("Invalid argument value");
	case CL_INVALID_ARG_SIZE:                 return std::string("Invalid argument size");
	case CL_INVALID_KERNEL_ARGS:              return std::string("Invalid kernel arguments");
	case CL_INVALID_WORK_DIMENSION:           return std::string("Invalid work dimension");
	case CL_INVALID_WORK_GROUP_SIZE:          return std::string("Invalid work group size");
	case CL_INVALID_WORK_ITEM_SIZE:           return std::string("Invalid work item size");
	case CL_INVALID_GLOBAL_OFFSET:            return std::string("Invalid global offset");
	case CL_INVALID_EVENT_WAIT_LIST:          return std::string("Invalid event wait list");
	case CL_INVALID_EVENT:                    return std::string("Invalid event");
	case CL_INVALID_OPERATION:                return std::string("Invalid operation");
	case CL_INVALID_GL_OBJECT:                return std::string("Invalid OpenGL object");
	case CL_INVALID_BUFFER_SIZE:              return std::string("Invalid buffer size");
	case CL_INVALID_MIP_LEVEL:                return std::string("Invalid mip-map level");
	case CL_INVALID_GLOBAL_WORK_SIZE:         return std::string("Invalid gloal work size");
	case CL_INVALID_PROPERTY:                 return std::string("Invalid property");
	default:                                  return std::string("Unknown error code");
	}
}

void Board::advanceSequentially()
{	
	int sum = 0;
	std::vector<std::vector<int>> newState = gamestate;
	int x = dimensions[0];
	int y = dimensions[1];
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			sum = -gamestate[i][j];

			if (i != 0 && i != y - 1 && j != 0 && j != x - 1) {
				for (int a = -1; a <= 1; ++a) {
					for (int b = -1; b <= 1; ++b) {
						sum += gamestate[i + a][j + b];
					}
				}
			}
			else {
				for (int a = -1; a <= 1; ++a) {
					int indexA = (i + a % y + y) % y;

					for (int b = -1; b <= 1; ++b) {
						sum += gamestate[indexA][(j + b % x + x) % x];
					}
				}
			}

			if (gamestate[i][j] == 1 && sum != 2 && sum != 3) {
				newState[i][j] = 0;
			}
			else if (gamestate[i][j] == 0 && sum == 3) {
				newState[i][j] = 1;
			}
		}
	}

	gamestate = newState;
}

void Board::advanceOpenMP()
{
	int sum = 0;
	std::vector<std::vector<int>> newState = gamestate;
	int x = dimensions[0];
	int y = dimensions[1];
	
	#pragma omp parallel for
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			sum = -gamestate[i][j];

			if (i != 0 && i != y - 1 && j != 0 && j != x - 1) {
				for (int a = -1; a <= 1; ++a) {
					for (int b = -1; b <= 1; ++b) {
						sum += gamestate[i + a][j + b];
					}
				}
			}
			else {
				for (int a = -1; a <= 1; ++a) {
					int indexA = (i + a % y + y) % y;

					for (int b = -1; b <= 1; ++b) {
						sum += gamestate[indexA][(j + b % x + x) % x];
					}
				}
			}

			if (gamestate[i][j] == 1 && sum != 2 && sum != 3) {
				newState[i][j] = 0;
			}
			else if (gamestate[i][j] == 0 && sum == 3) {
				newState[i][j] = 1;
			}
		}
	}

	gamestate = newState;
}

void Board::setupOpenCL(const int& width, const int height, unsigned __int64 deviceType, int platformId, int deviceID)
{
	data = vector<cl_int>(dimensions[0] * dimensions[1]);
	for (int i = 0; i < dimensions[1]; i++) {
		for (int j = 0; j < dimensions[0]; j++) {
			data[i * dimensions[0] + j] = gamestate[i][j];
		}
	}

	cl::Platform::get(&platforms);
	platform = platforms[platformId];
	cl_context_properties properties[] =
	{ CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(), 0 };
	cl::Context context(deviceType == 0 ? CL_DEVICE_TYPE_CPU : CL_DEVICE_TYPE_GPU, properties);

	devices = context.getInfo<CL_CONTEXT_DEVICES>();

	device = devices[deviceID];
	std::ifstream kernelFile(KERNEL_FILE);
	if (!kernelFile)
	{
		std::cout << "kernel source file " << KERNEL_FILE << " not found!" << std::endl;
	}

	std::string sourceCode(
		std::istreambuf_iterator<char>(kernelFile),
		(std::istreambuf_iterator<char>()));
	cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
	program = cl::Program(context, source);

	cl_int error = program.build(devices);
	kernel = cl::Kernel(program, "golKernel", &error);

	gamestateBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int) * dimensions[0] * dimensions[1]);
	newstateBuffer = cl::Buffer(context, CL_MEM_READ_WRITE, sizeof(int) * dimensions[0] * dimensions[1]);

	cl_int clWidth = dimensions[0];
	cl_int clHeight = dimensions[1];

	kernel.setArg(0, gamestateBuffer);
	kernel.setArg(1, newstateBuffer);
	kernel.setArg(2, clWidth);
	kernel.setArg(3, clHeight);

	queue = cl::CommandQueue(context, device);

	queue.enqueueWriteBuffer(gamestateBuffer, CL_TRUE, 0, sizeof(int) * dimensions[0] * dimensions[1], data.data());
}

void Board::advanceOpenCL()
{
	queue.enqueueNDRangeKernel(kernel, 0, cl::NDRange(dimensions[0] * dimensions[1]), cl::NullRange);
	queue.enqueueCopyBuffer(newstateBuffer, gamestateBuffer, 0, 0, sizeof(int) * dimensions[0] * dimensions[1]);
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

void Board::advanceGenerationsBy(int count, PARALLEL_MODE mode)
{
	switch (mode) {
	case eSequential:
		for (int i = 0; i < count; i++) {
			this->advanceSequentially();
		}
		break;
	case eOpenMP:
		for (int i = 0; i < count; i++) {
			this->advanceOpenMP();
		}
		break;
	case eOpenCL:
		for (int i = 0; i < count; i++) {
			this->advanceOpenCL();
		}

		queue.enqueueReadBuffer(newstateBuffer, CL_TRUE, 0, sizeof(int) * dimensions[0] * dimensions[1], data.data());
		queue.finish();

		break;
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
