#include "floatGenerator.h"

floatGenerator::floatGenerator(float min, float max) 
{
	if (min >= max) throw std::exception("Invalid generator configuration");
	std::random_device rd;
	gen.seed(rd());
	dist = std::uniform_real_distribution<>(min, max);
}

float floatGenerator::operator()()
{
	return dist(gen);
}
