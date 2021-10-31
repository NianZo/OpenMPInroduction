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
#include <array>
#include <numeric>

constexpr long NUM_STEPS = 100000;
constexpr int NUM_THREADS = 16;

int main()
{
	omp_set_num_threads(NUM_THREADS);
	std::array<double, NUM_THREADS> sum;

	constexpr double step = 1.0 / static_cast<double>(NUM_STEPS);

	assert(NUM_STEPS % omp_get_num_threads() == 0); // For simplicity I am assuming that numThreads evenly divides NUM_STEPS

	const double startTime = omp_get_wtime();
#pragma omp parallel
	{
		double localSum = 0.0;
		const uint32_t stepsPerThread = static_cast<uint32_t>(NUM_STEPS / omp_get_num_threads());
		const uint32_t threadId = static_cast<uint32_t>(omp_get_thread_num());
		for (uint i = threadId * stepsPerThread; i < (threadId + 1) * stepsPerThread; i++)
		{
			const double x = (i + 0.5) * step;
			localSum += 4.0 / (1.0 + x * x);
		}
		sum[threadId] = localSum;
	}
	double finalSum = std::accumulate(sum.begin(), sum.end(), 0.0);
	const double endTime = omp_get_wtime();
	const double pi = step * finalSum;
	std::cout << "Integral value: " << pi << std::endl;
	std::cout << "True value of pi: " << std::numbers::pi << std::endl;
	std::cout << "Calculation time: " << endTime - startTime << std::endl;
}


