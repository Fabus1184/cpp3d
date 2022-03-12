#include "Misc.h"

template<typename T>
void printArray(T arr[], int size, int width)
{
	for (int i = 0; i < width; i++) std::cout << "-";
	std::cout << std::endl;

	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << ", ";
		if ((i + 1) % width == 0) std::cout << std::endl;
	}

	for (int i = 0; i < width; i++) std::cout << "-";
	std::cout << std::endl;
}

// Manual instantiation because otherwise broken
template void printArray(float arr[], int size, int width = DEFAULT_WIDTH);