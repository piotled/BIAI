#pragma once
#include <random>
#include "IDoubleSource.h"

/*
	Generates random double number from specified range
*/

class DoubleGenerator : public IDoubleSource {
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

	/*
		Get number, from interface
	*/

	virtual double get() {
		return (*this)();
	}
};