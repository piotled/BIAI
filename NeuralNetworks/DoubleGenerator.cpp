#include "DoubleGenerator.h"

DoubleGenerator::DoubleGenerator(double min, double max) 
{
	if (min >= max) throw std::exception("Invalid generator configuration");
	std::random_device rd;
	gen.seed(rd());
	dist = std::uniform_real_distribution<>(min, max);
}

double DoubleGenerator::operator()()
{
	return dist(gen);
}
