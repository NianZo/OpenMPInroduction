/*
 * IntegrateToPi.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: nic
 */

#include <omp.h>
#include <iostream>
#include <numbers>
#include <cassert>

constexpr long NUM_STEPS = 100000;

int main()
{
	double sum = 0.0;

	constexpr double step = 1.0 / static_cast<double>(NUM_STEPS);
	omp_set_num_threads(16);
	assert(NUM_STEPS % omp_get_num_threads() == 0); // For simplicity I am assuming that numThreads evenly divides NUM_STEPS

	const double startTime = omp_get_wtime();
#pragma omp parallel
	{
		double localSum = 0.0;
		const int stepsPerThread = NUM_STEPS / omp_get_num_threads();
		const int threadId = omp_get_thread_num();
		for (int i = threadId * stepsPerThread; i < (threadId + 1) * stepsPerThread; i++)
		{
			const double x = (i + 0.5) * step;
			localSum += 4.0 / (1.0 + x * x);
		}
		sum += localSum; // Needs synchronization! Missing writes
	}
	const double endTime = omp_get_wtime();
	const double pi = step * sum;
	std::cout << "Integral value: " << pi << std::endl;
	std::cout << "True value of pi: " << std::numbers::pi << std::endl;
	std::cout << "Calculation time: " << endTime - startTime << std::endl;
}


