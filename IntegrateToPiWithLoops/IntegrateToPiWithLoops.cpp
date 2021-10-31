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

constexpr long NUM_STEPS = 1000000000;

int main()
{
	constexpr double step = 1.0 / static_cast<double>(NUM_STEPS);
	double sum = 0.0;

	const double startTime = omp_get_wtime();
#pragma omp parallel for reduction(+:sum)
	for (uint i = 0; i < NUM_STEPS; i++)
	{
		const double x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}

	const double endTime = omp_get_wtime();
	const double pi = step * sum;

	// Final output
	std::cout << "Integral value: " << pi << std::endl;
	std::cout << "True value of pi: " << std::numbers::pi << std::endl;
	std::cout << "Calculation time: " << endTime - startTime << std::endl;
}


