#define _USE_MATH_DEFINES	// This must be before all includes, in order for the M_PI to come in the cmath include

#include <iostream>
#include <chrono>
#include <cmath>

double totalSin()
{
	double total = 0;
	for (double angle = 0; angle < 1000000; angle += M_PI / 100.0)
	{
		total += std::sin(angle);
	}

	return total;
}

int main()
{
	//
	// Grab the starting time
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

	//
	// Call a long running function we want to time
	std::cout << "The total sin value is: " << totalSin() << std::endl;

	//
	// Grab the ending time
	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	//
	// Compute how long it took, then display that duration in seconds.
	std::chrono::duration<double> time = end - start;
	std::cout << "The execution time in seconds is: " << time.count() << std::endl;

	return 0;
}
