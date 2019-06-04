#pragma once
#include <random>
#include "IFloatSource.h"

/*
	Generates random float number from specified range
*/

class floatGenerator : public IFloatSource {
	std::mt19937 gen;
	std::uniform_real_distribution<> dist;
public:
	/*
		Constructs generator. Parameters: range bounds
	*/
	floatGenerator(float min, float max);

	/*
		Get number
	*/

	float operator()();

	/*
		Get number, from interface
	*/

	virtual float get() {
		return (*this)();
	}
};