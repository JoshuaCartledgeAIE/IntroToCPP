
#include <iostream>

int main()
{
	const int GRID_WIDTH = 5;
	const int GRID_HEIGHT = 6;

	int data[GRID_HEIGHT][GRID_WIDTH] = {
		{1,3,5,3,8},
		{1,2,5,3,8},
		{1,3,5,3,8},
		{21,3,5,9,2},
		{1,3,5,3,8},
		{14,3,5,3,8},
	};

	// add rows and print result
	for (int y = 0; y < GRID_HEIGHT; y++) {
		int total = 0;
		for (int x = 0; x < GRID_WIDTH; x++) {
			total += data[y][x];
		}
		std::cout << total << std::endl;
	}

	std::cout << "Column Sums:" << std::endl;

	// add columns and print result
	for (int x = 0; x < GRID_WIDTH; x++) {
		int total = 0;
		for (int y = 0; y < GRID_HEIGHT; y++) {
			total += data[y][x];
		}
		std::cout << total << std::endl;
	}

	// print array contents in order
	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			std::cout << data[y][x] << " ";
		}
		std::cout << std::endl;
	}
}

