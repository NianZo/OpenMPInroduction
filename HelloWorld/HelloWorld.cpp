/*
 * HelloWorld.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: nic
 */

#include <iostream>
#include <omp.h>

int main()
{
#pragma omp parallel
	{
	int id = omp_get_thread_num();
	std::cout << "hello" << id;
	std::cout << "world" << id << std::endl;
	}
}


