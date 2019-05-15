#pragma once
#include <random>

/*
	Generates random double number from specified range
*/

class DoubleGenerator {
	std::mt19937 gen;
	std::uniform_real_distribution<> dist;
public:
	/*
		Constructs generator. Parameters: range bounds
	*/
	DoubleGenerator(double min, double max);

	/*
		Get number
	*/

	double operator()();
};